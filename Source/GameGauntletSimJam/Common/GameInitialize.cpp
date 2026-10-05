#include "GameInitialize.h"

AGameInitialize::AGameInitialize() {}

void AGameInitialize::BeginPlay()
{
	Super::BeginPlay();
	
	UMoneyManager* MoneyManager = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if(MoneyManager) MoneyManager->Reset(InitialMoney);

	UTrackerManager* TrackerManager = GetGameInstance()->GetSubsystem<UTrackerManager>();
	if (TrackerManager) TrackerManager->Reset(BaseTrackInterval);
}
