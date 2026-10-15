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
	EmptyBuildingPanel->OnCloseButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleCloseButtonPressed);
	BuildingPanel->OnUpgradeButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleUpgradeButtonPressed);
	BuildingPanel->OnDemolishButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleDemolishButtonPressed);
	BuildingPanel->OnCloseButtonPressed.AddDynamic(this, &UBuildingControlUI::HandleCloseButtonPressed);
}

void UBuildingControlUI::HandlePlotSelected()
{
	APlot* Plot = ViewModel->GetSelectedPlot();
	if (!Plot) return;

	if (Plot->Building)
	{
		BuildingPanel->Show(Plot->PlotNumber, Plot->Building);
		EmptyBuildingPanel->Hide();
	}
	else
	{
		EmptyBuildingPanel->Show(Plot->PlotNumber);
		BuildingPanel->Hide();
	}

	if (!bIsShown)
	{
		bIsShown = true;
		OnShowBP();
	}
}

void UBuildingControlUI::HandleBuildButtonPressed(TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (!bIsShown) return;

	if (ViewModel) ViewModel->BuildRequested(BuildingBlueprint);
	HandlePlotSelected();
}

void UBuildingControlUI::HandleUpgradeButtonPressed()
{
	if (!bIsShown) return;

	if (ViewModel) ViewModel->UpgradeRequested();
	HandlePlotSelected();
}

void UBuildingControlUI::HandleDemolishButtonPressed()
{
	if (!bIsShown) return;

	if (ViewModel) ViewModel->DemolishRequested();
	BuildingPanel->Hide();
	HandleCloseButtonPressed();
}

void UBuildingControlUI::HandleCloseButtonPressed()
{
	if (!bIsShown) return;

	bIsShown = false;
	OnHideBP();
}
