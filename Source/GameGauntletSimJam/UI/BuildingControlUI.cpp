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

	BuildShopButton->OnClicked.AddDynamic(this, &UBuildingControlUI::HandleBuildShop);
	CloseButton->OnClicked.AddDynamic(this, &UBuildingControlUI::Hide);

	if (CostText && ShopBlueprint)
	{
		const int32 Cost = ShopBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		CostText->SetText(FText::AsNumber(Cost));
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