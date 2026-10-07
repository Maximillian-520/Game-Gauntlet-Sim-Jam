#include "BuildingPanelUI.h"

void UBuildingPanelUI::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());

	CloseButton->OnClicked.AddDynamic(this, &UBuildingPanelUI::Hide);
	UpgradeButton->OnClicked.AddDynamic(this, &UBuildingPanelUI::HandleUpgradeButtonPressed);
	DemolishButton->OnClicked.AddDynamic(this, &UBuildingPanelUI::HandleDemolishButtonPressed);
	if (MoneyManager) MoneyManager->OnMoneyChanged.AddDynamic(this, &UBuildingPanelUI::HandleMoneyChanged);

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
	if (UpgradeCostText)
	{
		if (Building->IsMaxLevel())
		{
			UpgradeCostText->SetText(FText::FromString("Max Level"));
			UpgradeButton->SetIsEnabled(false);
		}
		else
		{
			UpgradeCost = Building->GetUpgradeCost();
			const FString FormattedCostText = FString::Printf(TEXT("-$%d"), UpgradeCost);
			UpgradeCostText->SetText(FText::FromString(FormattedCostText));
		}
	}

	// Setup demolish
	if (DemolishValueText)
	{
		const int32 DemolishValue = Building->GetDemolishValue();
		const FString FormattedValueText = FString::Printf(TEXT("+$%d"), DemolishValue);
		DemolishValueText->SetText(FText::FromString(FormattedValueText));
	}

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
