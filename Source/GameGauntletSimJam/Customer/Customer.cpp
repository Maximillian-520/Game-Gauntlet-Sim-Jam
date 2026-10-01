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

	CustomerBehaviorComponent->OnShoppingFinished.AddDynamic(this, &ACustomer::HandleShoppingFinished);

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
	if (FMath::FRand() < InterestedChance) CustomerBehaviorComponent->GoToShop(Shop);
}

void ACustomer::GoToExit()
{
	CustomerBehaviorComponent->ChangeState(EBehaviorState::Exiting);
}

void ACustomer::HandleShoppingFinished(AShop* Shop)
{
	if (FMath::FRand() < PurchaseChance) OnPurchasedFromShop.Broadcast(Shop->ItemCost);
}
