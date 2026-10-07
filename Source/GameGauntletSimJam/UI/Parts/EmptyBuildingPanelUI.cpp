#include "EmptyBuildingPanelUI.h"


void UEmptyBuildingPanelUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());

	CloseButton->OnClicked.AddDynamic(this, &UEmptyBuildingPanelUI::Hide);
	BuildShopButton->OnClicked.AddDynamic(this, &UEmptyBuildingPanelUI::HandleBuildShopButtonPressed);
	BuildTrackerButton->OnClicked.AddDynamic(this, &UEmptyBuildingPanelUI::HandleBuildTrackerButtonPressed);
	if (MoneyManager) MoneyManager->OnMoneyChanged.AddDynamic(this, &UEmptyBuildingPanelUI::HandleMoneyChanged);

	Hide();
}

void UEmptyBuildingPanelUI::Show(int32 PlotNumber)
{
	const FString FormattedBuildingText = FString::Printf(TEXT("Empty Plot #%03d"), PlotNumber);
	BuildingText->SetText(FText::FromString(FormattedBuildingText));

	if (ShopCostText && ShopBlueprint)
	{
		ShopCost = ShopBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		const FString FormattedCostText = FString::Printf(TEXT("-$%d"), ShopCost);
		ShopCostText->SetText(FText::FromString(FormattedCostText));
	}

	if (TrackerCostText && TrackerBlueprint)
	{
		TrackerCost = TrackerBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		const FString FormattedCostText = FString::Printf(TEXT("-$%d"), TrackerCost);
		TrackerCostText->SetText(FText::FromString(FormattedCostText));
	}

	UpdatePanel();

	SetVisibility(ESlateVisibility::Visible);
}

void UEmptyBuildingPanelUI::Hide()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UEmptyBuildingPanelUI::UpdatePanel()
{
	BuildShopButton->SetIsEnabled(MoneyManager->GetMoney() >= ShopCost);
	BuildTrackerButton->SetIsEnabled(MoneyManager->GetMoney() >= TrackerCost);
}
