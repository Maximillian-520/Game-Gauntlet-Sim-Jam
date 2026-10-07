#include "BuildingControlUI.h"

void UBuildingControlUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ViewModel = NewObject<UBuildingViewModel>(this);

	if (ABuildingController* Controller = Cast<ABuildingController>(
		UGameplayStatics::GetActorOfClass(this, ABuildingController::StaticClass())))
	{
		ViewModel->Initialize(Controller);
	}

	ViewModel->OnPlotSelected.AddDynamic(this, &UBuildingControlUI::HandlePlotSelected);

	EmptyBuildingPanel->OnBuildButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleBuildButtonPressed);
	BuildingPanel->OnUpgradeButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleUpgradeButtonPressed);
	BuildingPanel->OnDemolishButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleDemolishButtonPressed);
}

void UBuildingControlUI::HandlePlotSelected()
{
	APlot* Plot = ViewModel->GetSelectedPlot();
	if (!Plot) return;

	if (Plot->Building)
	{
		EmptyBuildingPanel->Hide();
		BuildingPanel->Show(Plot->PlotNumber, Plot->Building);
	}
	else
	{
		EmptyBuildingPanel->Show(Plot->PlotNumber);
		BuildingPanel->Hide();
	}
}

void UBuildingControlUI::HandleBuildButtonPressed(TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (ViewModel) ViewModel->BuildRequested(BuildingBlueprint);
	EmptyBuildingPanel->Hide();
}

void UBuildingControlUI::HandleUpgradeButtonPressed()
{
	if (ViewModel) ViewModel->UpgradeRequested();
	BuildingPanel->Hide();
}

void UBuildingControlUI::HandleDemolishButtonPressed()
{
	if (ViewModel) ViewModel->DemolishRequested();
	BuildingPanel->Hide();
}