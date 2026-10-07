#include "BuildingViewModel.h"

void UBuildingViewModel::Initialize(ABuildingController* InController)
{
	if (!InController) return;

	Controller = InController;
	Controller->OnPlotClicked.AddUniqueDynamic(this, &UBuildingViewModel::HandlePlotClicked);
}

void UBuildingViewModel::BuildRequested(TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (!SelectedPlot || !BuildingBlueprint) return;

	Controller->BuildOnPlot(SelectedPlot, BuildingBlueprint);
}

void UBuildingViewModel::UpgradeRequested()
{
	if (!SelectedPlot) return;

	Controller->UpgradeOnPlot(SelectedPlot);
}

void UBuildingViewModel::DemolishRequested()
{
	if (!SelectedPlot) return;

	Controller->DemolishOnPlot(SelectedPlot);
}

void UBuildingViewModel::HandlePlotClicked(APlot* Plot)
{
	SelectedPlot = Plot;
	OnPlotSelected.Broadcast();
}