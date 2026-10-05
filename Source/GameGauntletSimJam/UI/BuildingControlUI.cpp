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

	CloseButton->OnClicked.AddDynamic(this, &UBuildingControlUI::Hide);
	BuildShopButton->OnClicked.AddDynamic(this, &UBuildingControlUI::HandleBuildShop);
	BuildTrackerButton->OnClicked.AddDynamic(this, &UBuildingControlUI::HandleBuildTracker);

	if (ShopCostText && ShopBlueprint)
	{
		const int32 Cost = ShopBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		ShopCostText->SetText(FText::AsNumber(Cost));
	}

	if (TrackerCostText && TrackerBlueprint)
	{
		const int32 Cost = TrackerBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		TrackerCostText->SetText(FText::AsNumber(Cost));
	}

	Hide();
}

void UBuildingControlUI::Show()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UBuildingControlUI::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UBuildingControlUI::HandlePlotSelected()
{
	Show();
}

void UBuildingControlUI::HandleBuildShop()
{
	if (ViewModel) ViewModel->BuildRequested(ShopBlueprint);
	Hide();
}

void UBuildingControlUI::HandleBuildTracker()
{
	if (ViewModel) ViewModel->BuildRequested(TrackerBlueprint);
	Hide();
}