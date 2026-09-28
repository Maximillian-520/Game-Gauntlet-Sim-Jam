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

	if (!LinearMovementComponent || (!bGoingToDisembarkLocation && !bGoingToDisappearLocation)) return;

	const FVector ToTarget = CurrentTargetLocation - GetActorLocation();
	const float DistanceToTarget = ToTarget.Size();
	const float CurrentSpeed = LinearMovementComponent->GetVelocity();

	// Close enough to reach the target this frame (also prevents overshooting)
	if (DistanceToTarget <= FMath::Max(CurrentSpeed * DeltaTime, 1.f))
	{
		HandlePointReached();
		return;
	}

	LinearMovementComponent->SetDirection(ToTarget);

	// Distance needed to come to a stop at the current speed: v^2 / (2 * decel)
	const float BrakeDecel = FMath::Max(LinearMovementComponent->BrakeDeceleration, KINDA_SMALL_NUMBER);
	const float StoppingDistance = (CurrentSpeed * CurrentSpeed) / (2.f * BrakeDecel);
	
	// Ignore brake if going to disappear
	if (bGoingToDisappearLocation)
	{
		LinearMovementComponent->Forward();
		return;
	}

	// Only brake once we're moving; otherwise a very short trip would never start
	if (CurrentSpeed > KINDA_SMALL_NUMBER && DistanceToTarget <= StoppingDistance)
	{
		LinearMovementComponent->Brake();

		// Fully stopped: finish the trip (snaps the last tiny gap)
		if (LinearMovementComponent->GetVelocity() <= 1.f) HandlePointReached();
	}
	else LinearMovementComponent->Forward();
}

void ATrain::GoToDisembarkLocation(const FVector& DisembarkLocation)
{
	CurrentTargetLocation = DisembarkLocation;
	bGoingToDisembarkLocation = true;
	bGoingToDisappearLocation = false;

	LinearMovementComponent->SetVelocity(LinearMovementComponent->MoveSpeed);
}

void ATrain::GoToDisappearLocation(const FVector& DisappearLocation)
{
	CurrentTargetLocation = DisappearLocation;
	bGoingToDisembarkLocation = false;
	bGoingToDisappearLocation = true;
}

void ATrain::HandlePointReached()
{
	// Stop and snap exactly onto the target
	if (LinearMovementComponent) LinearMovementComponent->SetVelocity(0.f);
	SetActorLocation(CurrentTargetLocation);

	if (bGoingToDisembarkLocation)
	{
		bGoingToDisembarkLocation = false;
		OnDisembarkLocationReached.Broadcast();
	}
	else if (bGoingToDisappearLocation)
	{
		bGoingToDisappearLocation = false;
		OnDisappearLocationReached.Broadcast();
	}
}
