#include "BuildingViewModel.h"

void UBuildingViewModel::Initialize(ABuildingController* InController)
{
	if (!InController) return;

	Controller = InController;
	Controller->OnPlotClicked.AddUniqueDynamic(this, &UBuildingViewModel::HandlePlotClicked);
}

void UBuildingViewModel::HandlePlotClicked(APlot* Plot)
{
	SelectedPlot = Plot;
	OnPlotSelected.Broadcast();
}

void UBuildingViewModel::BuildRequested(TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (!SelectedPlot || !BuildingBlueprint) return;

	Controller->BuildOnPlot(SelectedPlot, BuildingBlueprint);
}