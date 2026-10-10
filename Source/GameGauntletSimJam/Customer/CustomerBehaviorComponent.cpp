#include "CustomerBehaviorComponent.h"

UCustomerBehaviorComponent::UCustomerBehaviorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCustomerBehaviorComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (!Owner)
	{
		State = EBehaviorState::Disabled;
		return;
	}

	MovementComponent = Owner->FindComponentByClass<UCrowdMovementComponent>();
	if (!MovementComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: no UNavigationMovementComponent found, disabling."), *GetNameSafe(Owner));
		State = EBehaviorState::Disabled;
		SetComponentTickEnabled(false);
		return;
	}
	MovementComponent->OnPointReached.AddDynamic(this, &UCustomerBehaviorComponent::HandlePointReached);

	// Initialize to idle state
	State = EBehaviorState::Idle;
	EnterState(EBehaviorState::Idle);
}

void UCustomerBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateState(DeltaTime);
}

// ==================================================
//           State
// ==================================================

void UCustomerBehaviorComponent::ChangeState(EBehaviorState NewState)
{
	if (NewState == State) return;

	ExitState(State);
	State = NewState;
	EnterState(State);
}

void UCustomerBehaviorComponent::EnterState(EBehaviorState EnterState)
{
	if (!MovementComponent) return;

	switch (EnterState)
	{
		case EBehaviorState::Idle:
			MovementComponent->StopMovingToPoint();
			break;

		case EBehaviorState::Strolling:
			MovementComponent->MoveToPoint(ExitLocation);
			break;

		case EBehaviorState::Shopping:
			if (TargetShop)
			{
				MovementComponent->MoveToPoint(TargetShop->GetStandingLocation(), TargetShop->GetStandingDirection());
				bHasReachedShop = false;
				ShopPeekTimer = FMath::FRandRange(MinPeekingDuration, MaxPeekingDuration);
			}
			else ChangeState(EBehaviorState::Strolling);
			break;

		case EBehaviorState::MakingWay:
			MovementComponent->MoveToPoint(MakeWayLocation);
			bHasMadeWay = false;
			MakeWayPatienceTimer = FMath::FRandRange(MinPatienceDuration, MaxPatienceDuration);
			break;

		case EBehaviorState::Disabled:
			MovementComponent->StopMovingToPoint();
			SetComponentTickEnabled(false);
			break;
	}
}

void UCustomerBehaviorComponent::ExitState(EBehaviorState ExitState)
{
	if (!MovementComponent) return;

	switch (ExitState)
	{
		case EBehaviorState::Strolling:
			MovementComponent->StopMovingToPoint();
			break;

		case EBehaviorState::Shopping:
			OnShoppingFinished.Broadcast(TargetShop);
			break;

		case EBehaviorState::Disabled:
			SetComponentTickEnabled(true);
			break;

		default:
			break;
	}
}

void UCustomerBehaviorComponent::UpdateState(float DeltaTime)
{
	if (!MovementComponent) return;

	switch (State)
	{
		case EBehaviorState::Strolling:
			break;

		case EBehaviorState::Shopping:
			if (bHasReachedShop)
			{
				ShopPeekTimer -= DeltaTime;
				if (ShopPeekTimer <= 0) ChangeState(EBehaviorState::Strolling);
			}
			break;

		case EBehaviorState::MakingWay:
			if (bHasMadeWay)
			{
				MakeWayPatienceTimer -= DeltaTime;
				if (MakeWayPatienceTimer <= 0)
					if (AActor* Owner = GetOwner()) Owner->Destroy();
			}
			break;

		default:
			break;
	}
}

// ==================================================
//           Strolling
// ==================================================

void UCustomerBehaviorComponent::SetExit(AActor* NewExitActor, const FVector& NewExitLocation)
{
	ExitActor = NewExitActor;
	ExitLocation = NewExitLocation;
}

// ==================================================
//           Shopping
// ==================================================

void UCustomerBehaviorComponent::GoToShop(AShop* Shop)
{
	TargetShop = Shop;

	ChangeState(EBehaviorState::Shopping);
}

// ==================================================
//           Making Way
// ==================================================

void UCustomerBehaviorComponent::DoMakeWay(AActor* NewMakeWayActor, const FVector& NewMakeWayLocation)
{
	MakeWayActor = NewMakeWayActor;
	MakeWayLocation = NewMakeWayLocation;

	ChangeState(EBehaviorState::MakingWay);
}

// ==================================================
//           Event
// ==================================================

void UCustomerBehaviorComponent::HandlePointReached()
{
	switch (State)
	{
		case EBehaviorState::Strolling:
			// Reached the exit, customer is done.
			if (AActor* Owner = GetOwner()) Owner->Destroy();
			break;

		case EBehaviorState::Shopping:
			// Arrived at the shop.
			bHasReachedShop = true;
			MovementComponent->StopMovingToPoint();
			break;

		case EBehaviorState::MakingWay:
			// Reached the exit while making way.
			bHasMadeWay = true;
			if (ExitActor == MakeWayActor)
				if (AActor* Owner = GetOwner()) Owner->Destroy();
			break;

		default:
			break;
	}
}