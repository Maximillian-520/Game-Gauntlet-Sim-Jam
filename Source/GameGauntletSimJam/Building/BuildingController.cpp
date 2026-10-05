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
	if (Plot) Plot->BuildBuilding(BuildingBlueprint);
}