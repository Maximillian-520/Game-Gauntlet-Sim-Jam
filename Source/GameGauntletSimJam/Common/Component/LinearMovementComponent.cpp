#include "LinearMovementComponent.h"

ULinearMovementComponent::ULinearMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	Direction = FVector::ForwardVector;
	Velocity = 0.f;
}

void ULinearMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void ULinearMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AActor* Owner = GetOwner();
	if (!Owner || FMath::IsNearlyZero(Velocity)) return;

	const FVector Delta = Direction * Velocity * DeltaTime;
	Owner->AddActorWorldOffset(Delta, /*bSweep=*/true);
}

// Speeds up toward MoveSpeed using Acceleration (units/sec^2).
// Call every frame while "forward" input is held.
void ULinearMovementComponent::Forward()
{
	const UWorld* World = GetWorld();
	if (!World) return;

	Velocity = FMath::Min(Velocity + Acceleration * World->GetDeltaSeconds(), MoveSpeed);
}

// Slows toward 0 using BrakeDeceleration (units/sec^2).
// Call every frame while "brake" input is held.
void ULinearMovementComponent::Brake()
{
	const UWorld* World = GetWorld();
	if (!World) return;

	Velocity = FMath::Max(Velocity - BrakeDeceleration * World->GetDeltaSeconds(), 0.f);
}

