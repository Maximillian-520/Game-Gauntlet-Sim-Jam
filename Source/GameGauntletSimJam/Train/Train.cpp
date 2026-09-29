#include "Train.h"

ATrain::ATrain()
{
	PrimaryActorTick.bCanEverTick = true;
	LinearMovementComponent = CreateDefaultSubobject<ULinearMovementComponent>(TEXT("LinearMovementComponent"));
}

void ATrain::BeginPlay()
{
	Super::BeginPlay();
}

void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!LinearMovementComponent) return;
	if (!bIsMoving) return;

	const FVector ToTarget = TargetLocation - GetActorLocation();
	const float DistanceToTarget = ToTarget.Size();

	LinearMovementComponent->SetDirection(ToTarget);
	LinearMovementComponent->Forward();

	// Close enough to reach the target this frame (also prevents overshooting)
	if (DistanceToTarget <= AcceptanceRadius)
	{
		HandlePointReached();
		return;
	}
}

void ATrain::GoToLocation(FVector NewTargetLocation)
{
	bIsMoving = true;
	TargetLocation = NewTargetLocation;
	LinearMovementComponent->SetVelocity(LinearMovementComponent->MoveSpeed);
}

void ATrain::HandlePointReached()
{
	// Destroy after reaching target location
	Destroy();
}
