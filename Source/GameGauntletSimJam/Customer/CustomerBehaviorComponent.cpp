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

	NavMovement = Owner->FindComponentByClass<UNavigationMovementComponent>();
	if (!NavMovement)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s: no UNavigationMovementComponent found, disabling."), *GetNameSafe(Owner));
		State = EBehaviorState::Disabled;
		SetComponentTickEnabled(false);
		return;
	}
	NavMovement->OnPointReached.AddDynamic(this, &UCustomerBehaviorComponent::HandlePointReached);

	// Initialize to idle state
	State = EBehaviorState::Idle;
	EnterState(EBehaviorState::Idle);
}

void UCustomerBehaviorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateState();
}

// ==================================================
//           State
// ==================================================

void UCustomerBehaviorComponent::GoToShop(AShop* Shop)
{
	TargetShop = Shop;

	ChangeState(EBehaviorState::Shopping);
}

void UCustomerBehaviorComponent::ChangeState(EBehaviorState NewState)
{
	if (NewState == State) return;

	ExitState(State);
	State = NewState;
	EnterState(State);
}

void UCustomerBehaviorComponent::EnterState(EBehaviorState EnterState)
{
	if (!NavMovement) return;

	switch (EnterState)
	{
		case EBehaviorState::Idle:
			NavMovement->StopMovingToPoint();
			break;

		case EBehaviorState::Exiting:
			NavMovement->MoveToPoint(ExitLocation);
			break;

		case EBehaviorState::Shopping:
			if (TargetShop) NavMovement->MoveToPoint(TargetShop->GetStandingLocation());
			else ChangeState(EBehaviorState::Exiting);
			break;

		case EBehaviorState::Disabled:
			NavMovement->StopMovingToPoint();
			SetComponentTickEnabled(false);
			break;
	}
}

void UCustomerBehaviorComponent::ExitState(EBehaviorState ExitState)
{
	if (!NavMovement) return;

	switch (ExitState)
	{
		case EBehaviorState::Exiting:
			NavMovement->StopMovingToPoint();
			break;

		case EBehaviorState::Shopping:
			break;

		case EBehaviorState::Disabled:
			SetComponentTickEnabled(true);
			break;

		default:
			break;
	}
}

void UCustomerBehaviorComponent::UpdateState()
{
	if (!NavMovement) return;

	switch (State)
	{
		case EBehaviorState::Exiting:
			break;

		case EBehaviorState::Shopping:
			break;

		default:
			break;
	}
}

// ==================================================
//           Event
// ==================================================

void UCustomerBehaviorComponent::HandlePointReached()
{
	switch (State)
	{
		case EBehaviorState::Exiting:
			// Reached the exit, customer is done.
			if (AActor* Owner = GetOwner()) Owner->Destroy();
			break;

		case EBehaviorState::Shopping:
			// Arrived at the shop; finished shopping, head out.
			ChangeState(EBehaviorState::Exiting);
			break;

		default:
			break;
	}
}