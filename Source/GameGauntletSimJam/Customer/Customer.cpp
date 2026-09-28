#include "Customer.h"

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

	NavigationMovementComponent = CreateDefaultSubobject<UNavigationMovementComponent>(TEXT("Navigation Movement"));
	CustomerBehaviorComponent = CreateDefaultSubobject<UCustomerBehaviorComponent>(TEXT("Customer Behavior"));
}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		this, &ACustomer::GoToExit
	);
}

void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomer::SeeShop(AShop* Shop)
{
	const float Chance = 0.3f;
	if (FMath::FRand() < Chance) CustomerBehaviorComponent->GoToShop(Shop);
}

void ACustomer::GoToExit()
{
	CustomerBehaviorComponent->ChangeState(EBehaviorState::Exiting);
}
