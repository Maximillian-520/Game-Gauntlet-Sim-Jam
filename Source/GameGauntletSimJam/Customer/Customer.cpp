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
		this, &ACustomer::StrollAround
	);
}

void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomer::StrollAround()
{
	CustomerBehaviorComponent->ChangeState(EBehaviorState::Strolling);
}

void ACustomer::SeeShop(AShop* Shop)
{
	if (FMath::FRand() < InterestedChance) CustomerBehaviorComponent->GoToShop(Shop);
}

void ACustomer::MakeWay(AActor* NewMakeWayActor, const FVector& MakeWayLocation)
{
	CustomerBehaviorComponent->DoMakeWay(NewMakeWayActor, MakeWayLocation);
}

void ACustomer::SetExit(AActor* NewExitActor, const FVector& NewExitLocation)
{
	CustomerBehaviorComponent->SetExit(NewExitActor, NewExitLocation);
}

void ACustomer::HandleShoppingFinished(AShop* Shop)
{
	if (FMath::FRand() < PurchaseChance) OnPurchasedFromShop.Broadcast(Shop->ItemCost);
}
