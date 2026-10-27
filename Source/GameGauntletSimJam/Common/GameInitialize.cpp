#include "GameInitialize.h"

AGameInitialize::AGameInitialize() {}

void AGameInitialize::BeginPlay()
{
	Super::BeginPlay();
	
	UMoneyManager* MoneyManager = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if(MoneyManager) MoneyManager->Reset(InitialMoney);

	UCustomerManager* CustomerManager = GetGameInstance()->GetSubsystem<UCustomerManager>();
	if (CustomerManager) CustomerManager->Reset(BaseSpawnInterval);

	UTrainManager* TrainManager = GetGameInstance()->GetSubsystem<UTrainManager>();
	if (TrainManager) TrainManager->Reset(BaseTrackInterval);
}
