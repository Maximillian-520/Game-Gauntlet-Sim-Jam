#include "BuildingPanelUI.h"

void UBuildingPanelUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());

	CloseButton->OnButtonClicked.AddDynamic(this, &UBuildingPanelUI::BroadcastOnCloseButtonPressed);
	UpgradeButton->OnButtonClicked.AddDynamic(this, &UBuildingPanelUI::HandleUpgradeButtonPressed);
	DemolishButton->OnButtonClicked.AddDynamic(this, &UBuildingPanelUI::HandleDemolishButtonPressed);
	if (MoneyManager) MoneyManager->OnMoneyChanged.AddDynamic(this, &UBuildingPanelUI::HandleMoneyChanged);

	CloseButton->SetButtonText(FText::FromString(CloseText));
	Hide();
}

void UBuildingPanelUI::Show(int32 PlotNumber, ABaseBuilding* Building)
{
	// Setup building text
	const FString FormattedBuildingText = FString::Printf(
		TEXT("%s #%03d"), *Building->BuildingName.ToString(), PlotNumber
	);
	BuildingText->SetText(FText::FromString(FormattedBuildingText));

	// Setup level text
	const FString FormattedLevelText = FString::Printf(TEXT("Lv. %d"), Building->GetCurrentLevel());
	LevelText->SetText(FText::FromString(FormattedLevelText));

	// Setup upgrade
	if (Building->IsMaxLevel())
	{
		UpgradeButton->SetButtonText(FText::FromString(MaxLevelText));
		UpgradeButton->SetIsEnabled(false);
	}
	else
	{
		UpgradeCost = Building->GetUpgradeCost();
		const FString FormattedCostText = FString::Printf(TEXT("-$%d"), UpgradeCost);
		UpgradeButton->SetButtonText(FText::FromString(FormattedCostText));
	}

	// Setup demolish
	const int32 DemolishValue = Building->GetDemolishValue();
	const FString FormattedValueText = FString::Printf(TEXT("+$%d"), DemolishValue);
	DemolishButton->SetButtonText(FText::FromString(FormattedValueText));

	CurrentBuilding = Building;
	UpdatePanel();

	SetVisibility(ESlateVisibility::Visible);
}

void UBuildingPanelUI::Hide()
{
	CurrentBuilding = nullptr;

	SetVisibility(ESlateVisibility::Collapsed);
}

void UBuildingPanelUI::UpdatePanel()
{
	if (!CurrentBuilding) return;

	bool bIsMaxLevel = CurrentBuilding->IsMaxLevel();
	bool bCanAfford = MoneyManager->GetMoney() >= UpgradeCost;

	UpgradeButton->SetIsEnabled(!bIsMaxLevel && bCanAfford);
}
