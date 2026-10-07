#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../../Building/BaseBuilding.h"
#include "../../Common/Manager/MoneyManager.h"
#include "BuildingPanelUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDemolishButtonPressed);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UBuildingPanelUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Show(int32 PlotNumber, ABaseBuilding* Building);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Hide();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdatePanel();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnUpgradeButtonPressed OnUpgradeButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnDemolishButtonPressed OnDemolishButtonPressed;

protected:
	virtual void NativeOnInitialized();

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BuildingText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// ==================================================
	//           Upgrade
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> UpgradeButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> UpgradeCostText;

	// ==================================================
	//           Demolish
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> DemolishButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> DemolishValueText;

	// ==================================================
	//           Event
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleUpgradeButtonPressed() { OnUpgradeButtonPressed.Broadcast(); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleDemolishButtonPressed() { OnDemolishButtonPressed.Broadcast(); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleMoneyChanged(int32 NewAmount, int32 Delta) { UpdatePanel(); }

private:
	UMoneyManager* MoneyManager;
	ABaseBuilding* CurrentBuilding;

	int32 UpgradeCost;
};
