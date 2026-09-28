#include "BasicMovementComponent.h"
#include "GameFramework/Actor.h"

UBasicMovementComponent::UBasicMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UBasicMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBasicMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	// Super call
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Check owner
	AActor* Owner = GetOwner();
	if (!Owner) return;
	// Set variables
	FVector Direction;

	// --- WASD movement ---
	if (ForwardInputValue != 0.f || RightInputValue != 0.f)
	{
		// Calculate direction
		const FRotator OwnerRotation = Owner->GetActorRotation();
		const FVector ForwardDir = FRotationMatrix(OwnerRotation).GetUnitAxis(EAxis::X);
		const FVector RightDir = FRotationMatrix(OwnerRotation).GetUnitAxis(EAxis::Y);
		// Calculate delta and apply
		Direction = (ForwardDir * ForwardInputValue + RightDir * RightInputValue).GetSafeNormal();
		FVector MoveDelta = Direction * MoveSpeed * DeltaTime;
		Owner->AddActorWorldOffset(MoveDelta, true);
		// Ignore rotate to face movement
		return;
	}

	// --- Direction movement ---
	else if (!CurrentFrameMoveDirection.IsNearlyZero())
	{
		Direction = CurrentFrameMoveDirection;
		FVector MoveDelta = Direction * MoveSpeed * DeltaTime;
		Owner->AddActorWorldOffset(MoveDelta, true);
		CurrentFrameMoveDirection = FVector::Zero();
	}

	// --- Move to point ---
	else if (bIsMovingToPoint)
	{
		// Calculate distance
		const FVector CurrentLocation = Owner->GetActorLocation();
		const FVector ToTarget = CurrentTargetlocation - CurrentLocation;
		const float DistanceToTarget = ToTarget.Size();
		// Check has arrived
		if (DistanceToTarget <= AcceptanceRadius)
		{
			Owner->SetActorLocation(CurrentTargetlocation);
			StopMovingToPoint();
			OnPointReached.Broadcast();
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

// ==================================================
//           WASD Movement
// ==================================================

void UBasicMovementComponent::MoveForward(float Value)
{
	if (bIsMovingToPoint) StopMovingToPoint();
	ForwardInputValue = Value;
}

void UBasicMovementComponent::MoveRight(float Value)
{
	if (bIsMovingToPoint) StopMovingToPoint();
	RightInputValue = Value;
}

// ==================================================
//           Move To Point
// ==================================================

void UBasicMovementComponent::MoveToPoint(const FVector& TargetLocation)
{
	CurrentTargetlocation = TargetLocation;
	bIsMovingToPoint = true;
}

void UBasicMovementComponent::StopMovingToPoint()
{
	bIsMovingToPoint = false;
}

// ==================================================
//           Move To Direction
// ==================================================

void UBasicMovementComponent::MoveToDirection(const FVector& Direction)
{
	if (bIsMovingToPoint) StopMovingToPoint();
	CurrentFrameMoveDirection = Direction;
}
