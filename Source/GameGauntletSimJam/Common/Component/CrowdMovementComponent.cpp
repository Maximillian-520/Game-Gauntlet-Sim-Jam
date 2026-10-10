#include "CrowdMovementComponent.h"

TArray<UCrowdMovementComponent*> UCrowdMovementComponent::ActiveAgents;

UCrowdMovementComponent::UCrowdMovementComponent() {}

void UCrowdMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	// Rolled once per agent so the crowd is not in lockstep
	AgentPhase = FMath::FRandRange(0.f, 2.f * PI);
	MoveSpeed *= FMath::FRandRange(SpeedMultiplierRange.X, SpeedMultiplierRange.Y);

	ActiveAgents.AddUnique(this);
}

void UCrowdMovementComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ActiveAgents.Remove(this);
	Super::EndPlay(EndPlayReason);
}

void UCrowdMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Only crowd-adjust agents that are still walking (base may have just arrived)
	if (!bIsMovingToPoint) return;
	AActor* Owner = GetOwner();
	if (!Owner) return;

	const FVector Location = Owner->GetActorLocation();
	FVector ToTarget = CurrentTargetlocation - Location;
	ToTarget.Z = 0.f;
	const FVector Forward = ToTarget.GetSafeNormal();

	FVector Offset = FVector::ZeroVector;

	// --- Wobble: sideways sway, fades out near the final destination ---
	if (WobbleAmplitude > 0.f && !Forward.IsNearlyZero())
	{
		const FVector Right = FVector::CrossProduct(FVector::UpVector, Forward);
		const FVector FinalPoint = CurrentPath.Num() > 0 ? CurrentPath.Last() : FinalTargetLocation;
		const float DistToFinal = FVector::Dist2D(Location, FinalPoint);
		const float Fade = FMath::Clamp(DistToFinal / ArrivalFadeDistance, 0.f, 1.f);

		// Derivative of A*sin(w*t + phase), so the net sway stays within +/- WobbleAmplitude
		const float Time = GetWorld()->GetTimeSeconds();
		const float SwayVelocity = FMath::Cos(Time * WobbleFrequency + AgentPhase)
			* WobbleAmplitude * WobbleFrequency * Fade;
		Offset += Right * SwayVelocity * DeltaTime;
	}

	// --- Separation: push away from nearby agents ---
	if (SeparationStrength > 0.f)
	{
		Offset += ComputeSeparation(Location) * DeltaTime;
	}

	if (!Offset.IsNearlyZero())
	{
		Owner->AddActorWorldOffset(Offset, true);
	}
}

void UCrowdMovementComponent::RequestPath(const FVector& TargetLocation)
{
	// Base builds CurrentPath / CurrentPathIndex / CurrentTargetlocation, or stops on failure
	Super::RequestPath(TargetLocation);

	if (!bIsMovingToPoint || !CurrentPath.IsValidIndex(CurrentPathIndex)) return;

	ApplyCrowdOffsetsToPath();

	// NavMesh points sit on the floor, the actor pivot usually doesn't. A constant Z gap keeps the
	// 3D distance check in the base class above AcceptanceRadius and the agent walks on the spot.
	if (bFlattenPathToActorHeight)
	{
		if (const AActor* Owner = GetOwner())
		{
			const float Z = Owner->GetActorLocation().Z;
			for (FVector& Point : CurrentPath)
			{
				Point.Z = Z;
			}
		}
	}

	CurrentTargetlocation = CurrentPath[CurrentPathIndex];
	UpdateAcceptanceRadiusForLeg();
}

void UCrowdMovementComponent::GoToNextWaypoint()
{
	Super::GoToNextWaypoint();

	// Still walking: roll the acceptance radius for the new leg
	if (bIsMovingToPoint)
	{
		UpdateAcceptanceRadiusForLeg();
	}
}

FVector UCrowdMovementComponent::ComputeSeparation(const FVector& MyLocation) const
{
	FVector Push = FVector::ZeroVector;
	if (SeparationRadius <= 0.f) return Push;

	for (const UCrowdMovementComponent* Other : ActiveAgents)
	{
		if (!Other || Other == this || Other->GetWorld() != GetWorld()) continue;
		const AActor* OtherOwner = Other->GetOwner();
		if (!OtherOwner) continue;

		FVector Away = MyLocation - OtherOwner->GetActorLocation();
		Away.Z = 0.f;
		const float Dist = Away.Size();
		if (Dist >= SeparationRadius) continue;

		// Exactly stacked agents: pick a random direction to break the tie
		if (Dist < KINDA_SMALL_NUMBER)
		{
			Away = FVector(FMath::FRandRange(-1.f, 1.f), FMath::FRandRange(-1.f, 1.f), 0.f);
		}

		// Closer neighbours push harder
		Push += Away.GetSafeNormal() * (1.f - Dist / SeparationRadius);
	}

	return Push.GetClampedToMaxSize(1.f) * SeparationStrength;
}

void UCrowdMovementComponent::UpdateAcceptanceRadiusForLeg()
{
	const bool bIsFinalPoint = CurrentPathIndex >= CurrentPath.Num() - 1;
	AcceptanceRadius = bIsFinalPoint
		? FinalAcceptanceRadius
		: FMath::FRandRange(IntermediateAcceptanceRadiusRange.X, IntermediateAcceptanceRadiusRange.Y);
}

void UCrowdMovementComponent::ApplyCrowdOffsetsToPath()
{
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
	if (!NavSys || CurrentPath.Num() == 0) return;

	const int32 LastIndex = CurrentPath.Num() - 1;

	// --- Lane offset: one sideways shift per trip, so the agent keeps a consistent "lane" ---
	if (MaxLaneOffset > 0.f)
	{
		const float Lane = FMath::FRandRange(-MaxLaneOffset, MaxLaneOffset);

		// Index 0 is the start point and the last index is the destination, only shift the ones between
		for (int32 i = 1; i < LastIndex; ++i)
		{
			FVector Dir = CurrentPath[i + 1] - CurrentPath[i - 1];
			Dir.Z = 0.f;
			Dir = Dir.GetSafeNormal();
			if (Dir.IsNearlyZero()) continue;

			const FVector Right = FVector::CrossProduct(FVector::UpVector, Dir);
			const FVector Candidate = CurrentPath[i] + Right * Lane;

			// Keep the shifted point on the NavMesh
			FNavLocation Projected;
			if (!NavSys->ProjectPointToNavigation(Candidate, Projected, NavProjectionExtent)) continue;

			// Reject shifts that would make the leg cross a NavMesh boundary (walls, corners)
			FVector HitLocation;
			if (UNavigationSystemV1::NavigationRaycast(GetWorld(), CurrentPath[i - 1], Projected.Location, HitLocation)) continue;

			CurrentPath[i] = Projected.Location;
		}
	}

	// --- Scatter the final point so agents sharing a destination don't stack on one spot ---
	if (FinalScatterRadius > 0.f)
	{
		FNavLocation Scattered;
		if (NavSys->GetRandomReachablePointInRadius(CurrentPath[LastIndex], FinalScatterRadius, Scattered))
		{
			const FVector From = (LastIndex > 0) ? CurrentPath[LastIndex - 1] : GetOwner()->GetActorLocation();
			FVector HitLocation;
			if (!UNavigationSystemV1::NavigationRaycast(GetWorld(), From, Scattered.Location, HitLocation))
			{
				CurrentPath[LastIndex] = Scattered.Location;
			}
		}
	}
}