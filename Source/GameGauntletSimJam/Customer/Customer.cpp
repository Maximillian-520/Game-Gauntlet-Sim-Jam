#include "Customer.h"

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;

	CrowdMovementComponent = CreateDefaultSubobject<UCrowdMovementComponent>(TEXT("CrowdMovement"));
	CustomerBehaviorComponent = CreateDefaultSubobject<UCustomerBehaviorComponent>(TEXT("CustomerBehavior"));
}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();

	CustomerBehaviorComponent->OnCustomerExited.AddDynamic(this, &ACustomer::HandleCustomerExited);
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
	bIsMakingWay = false;
	CustomerBehaviorComponent->ChangeState(EBehaviorState::Strolling);
}

void ACustomer::SeeBuilding(ABaseBuilding* Building)
{
	if (CustomerBehaviorComponent->IsMakingWay()) return;

	AShop* Shop = Cast<AShop>(Building);
	if (Shop)
	{
		if (FMath::FRand() < InterestedChance) CustomerBehaviorComponent->GoToShop(Shop);
	}
}

void ACustomer::MakeWay(AActor* MakeWayActor, const FVector& MakeWayLocation, const FRotator& MakeWayRotation)
{
	bIsMakingWay = true;
	CustomerBehaviorComponent->DoMakeWay(MakeWayActor, MakeWayLocation, MakeWayRotation);
}

void ACustomer::SetExit(AActor* ExitActor, const FVector& ExitLocation, const FRotator& ExitRotation)
{
	CustomerBehaviorComponent->SetExit(ExitActor, ExitLocation, ExitRotation);
}

void ACustomer::HandleCustomerExited()
{
	bIsActive = false;
	OnCustomerDestroy.Broadcast();
}

void ACustomer::HandleShoppingFinished(AShop* Shop)
{
	if (bIsMakingWay) return;

	if (FMath::FRand() < PurchaseChance)
	{
		OnPurchasedFromShop.Broadcast(Shop->GetItemCost());
		OnPurchasedFromShopBP(Shop->GetItemCost());
	}
}
