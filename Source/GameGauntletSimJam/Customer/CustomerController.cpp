#include "CustomerController.h"

ACustomerController::ACustomerController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerController::BeginPlay()
{
	Super::BeginPlay();
	
	CustomerManager = UGameInstance::GetSubsystem<UCustomerManager>(GetGameInstance());
	if (!CustomerManager) return;
	MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());
	if (!MoneyManager) return;

	CustomerSpawner->OnCustomerSpawned.AddDynamic(this, &ACustomerController::HandleCustomerSpawned);
	if (CustomerManager)
	{
		CustomerManager->OnSpawnIntervalChanged.AddDynamic(this, &ACustomerController::HandleSpawnIntervalChanged);
		CustomerManager->OnInterestedChanceChanged.AddDynamic(this, &ACustomerController::HandleInterestedChanceChanged);
	}

	UpdateSpawnInterval();
}

void ACustomerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomerController::StartMakingWay()
{
    for (ACustomer* Customer : Customers)
    {
        if (!Customer) continue;

		//if (!Customer->IsActive()) continue;

        UBoxComponent* SpawnArea = CustomerSpawner->GetNearestSpawnArea(Customer->GetActorLocation());
        if (SpawnArea)
		{
			Customer->MakeWay(
				SpawnArea->GetOwner(),
				CustomerSpawner->GetRandomPointInArea(SpawnArea),
				SpawnArea->GetOwner()->GetActorRotation()
			);
		}
    }

	CustomerSpawner->StopSpawning();

	OnStartMakingWayBP();
}

void ACustomerController::EndMakingWay()
{
	for (ACustomer* Customer : Customers)
	{
		if (!Customer) continue;

		Customer->StrollAround();
	}

	CustomerSpawner->StartSpawning();

	OnEndMakingWayBP();
}

void ACustomerController::UpdateSpawnInterval()
{
	if (CustomerSpawner && CustomerManager)
	{
		CustomerSpawner->MinSpawnInterval = CustomerManager->GetCalculatedSpawnInterval();
		CustomerSpawner->MaxSpawnInterval = CustomerManager->GetCalculatedSpawnInterval();
	}
}

void ACustomerController::HandleCustomerSpawned(ACustomer* Customer)
{
	Customer->OnPurchasedFromShop.AddDynamic(this, &ACustomerController::HandlePurchasedFromShop);
	Customer->OnDestroyed.AddDynamic(this, &ACustomerController::HandleCustomerDestroyed);
	Customers.Add(Customer);
}

void ACustomerController::HandlePurchasedFromShop(int32 MoneySpent)
{
	if (MoneyManager) MoneyManager->AddMoney(MoneySpent);
}

void ACustomerController::HandleCustomerDestroyed(AActor* DestroyedActor)
{
	Customers.Remove(Cast<ACustomer>(DestroyedActor));
}

void ACustomerController::HandleInterestedChanceChanged()
{
	if (CustomerSpawner && CustomerManager)
	{
		CustomerSpawner->InterestedChanceIncreaseModifier = CustomerManager->GetInterestedChanceIncrease();
	}
}

