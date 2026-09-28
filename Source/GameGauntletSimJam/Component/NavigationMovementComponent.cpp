#include "NavigationMovementComponent.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Actor.h"

UNavigationMovementComponent::UNavigationMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNavigationMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UNavigationMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Super call
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Check owner
	AActor* Owner = GetOwner();
	if (!Owner) return;
	// Set variables
	FVector Direction;

	// --- Move to point ---
	if (bIsMovingToPoint)
	{
		// Calculate distance
		const FVector CurrentLocation = Owner->GetActorLocation();
		const FVector ToTarget = CurrentTargetlocation - CurrentLocation;
		const float DistanceToTarget = ToTarget.Size();
		// Check has arrived
		if (DistanceToTarget <= AcceptanceRadius)
		{
			GoToNextWaypoint();
			return;
		}
		// Calculate direction and location
		Direction = ToTarget.GetSafeNormal();
		const float StepDistance = FMath::Min(MoveSpeed * DeltaTime, DistanceToTarget);
		const FVector NewLocation = CurrentLocation + Direction * StepDistance;
		// Set new location
		Owner->SetActorLocation(NewLocation, true);
	}

	// --- Rotate to face movement ----
	if (bRotateToFaceMovement && !Direction.IsNearlyZero())
	{
		const FRotator TargetRotation = Direction.Rotation();
		const FRotator NewRotation = FMath::RInterpConstantTo(
			Owner->GetActorRotation(),
			TargetRotation,
			DeltaTime,
			RotationSpeed);
		Owner->SetActorRotation(NewRotation);
	}
}

void UNavigationMovementComponent::MoveToPoint(const FVector& TargetLocation)
{
	UE_LOG(LogTemp, Warning, TEXT("MoveToPoint called. HasBegunPlay: %d, Owner: %s"),
		HasBegunPlay(),
		GetOwner() ? *GetOwner()->GetName() : TEXT("NULL"));

	FinalTargetlocation = TargetLocation;
	bIsMovingToPoint = true;
	RequestPath(TargetLocation);
}

void UNavigationMovementComponent::StopMovingToPoint()
{
	CurrentPath.Reset();
	CurrentPathIndex = INDEX_NONE;
	bIsMovingToPoint = false;
}

void UNavigationMovementComponent::RequestPath(const FVector& TargetLocation)
{
	AActor* Owner = GetOwner();
	if (!Owner) return;

	UWorld* World = GetWorld();
	UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(World);
	if (!NavSys)
	{
		// No nav system in this world
		StopMovingToPoint();
		return;
	}

	// Synchronous query - fine for occasional calls; switch to FindPathAsync if you're
	// issuing many of these per frame (e.g. spawning a crowd all at once).
	UNavigationPath* NavPath = NavSys->FindPathToLocationSynchronously(
		World,
		Owner->GetActorLocation(),
		TargetLocation
	);

	if (NavPath && NavPath->IsValid() && NavPath->PathPoints.Num() > 0)
	{
		CurrentPath = NavPath->PathPoints;

		// PathPoints[0] is typically the actor's current location - skip straight to the
		// next point if one exists so we don't "arrive" at our own starting position.
		CurrentPathIndex = (CurrentPath.Num() > 1) ? 1 : 0;
		CurrentTargetlocation = CurrentPath[CurrentPathIndex];
	}
	else
	{
		// No valid path (e.g. target off the NavMesh)
		StopMovingToPoint();
		return;
	}
}

void UNavigationMovementComponent::GoToNextWaypoint()
{
	CurrentPathIndex++;

	if (CurrentPath.IsValidIndex(CurrentPathIndex))
	{
		CurrentTargetlocation = CurrentPath[CurrentPathIndex];
	}
	else
	{
		// Reached the final path point
		AActor* Owner = GetOwner();
		if (Owner) Owner->SetActorLocation(CurrentTargetlocation);
		StopMovingToPoint();
		OnPointReached.Broadcast();
	}
}