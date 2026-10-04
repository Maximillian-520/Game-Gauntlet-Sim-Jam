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

	// Temp
	UMoneyManager* Money = GetGameInstance()->GetSubsystem<UMoneyManager>();
	Money->AddMoney(1000);
}

void ABuildingController::BuildOnPlot(APlot* Plot, TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (Plot) Plot->BuildBuilding(BuildingBlueprint);
}