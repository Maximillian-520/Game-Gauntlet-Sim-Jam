#include "BuildingController.h"

ABuildingController::ABuildingController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ABuildingController::BeginPlay()
{
	Super::BeginPlay();

	for (APlot* Plot : Plots)
	{
		Plot->OnPlotClicked.AddUniqueDynamic(this, &ABuildingController::HandlePlotClicked);
	}
}

void ABuildingController::BuildOnPlot(APlot* Plot, TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (!Plot) return;

	const int32 Cost = BuildingBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;

	UMoneyManager* MoneyManager = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if (MoneyManager && !MoneyManager->TrySpend(Cost)) return;

	Plot->BuildBuilding(BuildingBlueprint);
}

void ABuildingController::UpgradeOnPlot(APlot* Plot)
{
	if (!Plot) return;

	const int32 Cost = Plot->Building->GetUpgradeCost();

	UMoneyManager* MoneyManager = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if (MoneyManager && !MoneyManager->TrySpend(Cost)) return;

	Plot->UpgradeBuilding();
}

void ABuildingController::DemolishOnPlot(APlot* Plot)
{
	if (!Plot) return;

	const int32 Value = Plot->Building->GetDemolishValue();

	UMoneyManager* MoneyManager = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if (MoneyManager) MoneyManager->AddMoney(Value);

	Plot->DemolishBuilding();
}