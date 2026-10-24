#include "EmptyBuildingPanelUI.h"


void UEmptyBuildingPanelUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());

	CloseButton->OnButtonClicked.AddDynamic(this, &UEmptyBuildingPanelUI::BroadcastOnCloseButtonPressed);
	BuildShopButton->OnButtonClicked.AddDynamic(this, &UEmptyBuildingPanelUI::HandleBuildShopButtonPressed);
	BuildTrackerButton->OnButtonClicked.AddDynamic(this, &UEmptyBuildingPanelUI::HandleBuildTrackerButtonPressed);
	BuildDecorButton->OnButtonClicked.AddDynamic(this, &UEmptyBuildingPanelUI::HandleBuildDecorButtonPressed);
	if (MoneyManager) MoneyManager->OnMoneyChanged.AddDynamic(this, &UEmptyBuildingPanelUI::HandleMoneyChanged);

	CloseButton->SetButtonText(FText::FromString(CloseText));
	Hide();
}

void UEmptyBuildingPanelUI::Show(int32 PlotNumber)
{
	const FString FormattedBuildingText = FString::Printf(TEXT("Empty Plot #%03d"), PlotNumber);
	BuildingText->SetText(FText::FromString(FormattedBuildingText));

	if (ShopBlueprint)
	{
		ShopCost = ShopBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		const FString FormattedCostText = FString::Printf(TEXT("-$%d"), ShopCost);
		BuildShopButton->SetButtonText(FText::FromString(FormattedCostText));
	}

	if (TrackerBlueprint)
	{
		TrackerCost = TrackerBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		const FString FormattedCostText = FString::Printf(TEXT("-$%d"), TrackerCost);
		BuildTrackerButton->SetButtonText(FText::FromString(FormattedCostText));
	}

	if (DecorBlueprint)
	{
		DecorCost = DecorBlueprint->GetDefaultObject<ABaseBuilding>()->BuildCost;
		const FString FormattedCostText = FString::Printf(TEXT("-$%d"), DecorCost);
		BuildDecorButton->SetButtonText(FText::FromString(FormattedCostText));
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
	BuildDecorButton->SetIsEnabled(MoneyManager->GetMoney() >= DecorCost);
}
