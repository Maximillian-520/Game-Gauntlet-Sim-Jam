#include "CustomerController.h"

ACustomerController::ACustomerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerController::BeginPlay()
{
	Super::BeginPlay();
	
	CustomerSpawner->OnCustomerSpawned.AddDynamic(this, &ACustomerController::HandleCustomerSpawned);
}

void ACustomerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomerController::HandleCustomerSpawned(ACustomer* Customer)
{
	Customer->OnPurchasedFromShop.AddDynamic(this, &ACustomerController::HandlePurchasedFromShop);
	Customer->OnDestroyed.AddDynamic(this, &ACustomerController::HandleCustomerDestroyed);
	Customers.Add(Customer);
}

void ACustomerController::HandlePurchasedFromShop(int32 MoneySpent)
{
	if (UMoneyManager* MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance()))
	{
		MoneyManager->AddMoney(MoneySpent);
	}
}

void ACustomerController::HandleCustomerDestroyed(AActor* DestroyedActor)
{
	Customers.Remove(Cast<ACustomer>(DestroyedActor));
}

