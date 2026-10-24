#include "GameInitialize.h"

AGameInitialize::AGameInitialize() {}

void AGameInitialize::BeginPlay()
{
	Super::BeginPlay();
	
	UMoneyManager* MoneyManager = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if(MoneyManager) MoneyManager->Reset(InitialMoney);

	UCustomerManager* CustomerManager = GetGameInstance()->GetSubsystem<UCustomerManager>();
	if (CustomerManager) CustomerManager->Reset(BaseSpawnInterval);

	UTrackerManager* TrackerManager = GetGameInstance()->GetSubsystem<UTrackerManager>();
	if (TrackerManager) TrackerManager->Reset(BaseTrackInterval);
}
