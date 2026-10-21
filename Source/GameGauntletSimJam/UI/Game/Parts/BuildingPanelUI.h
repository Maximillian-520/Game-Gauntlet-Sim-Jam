#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "../../Component/BasicButton.h"
#include "../../../Building/BaseBuilding.h"
#include "../../../Common/Manager/MoneyManager.h"
#include "BuildingPanelUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpgradeButtonPressed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDemolishButtonPressed);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UBuildingPanelUI : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonPressed);

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

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCloseButtonPressed OnCloseButtonPressed;
	UFUNCTION()
	void BroadcastOnCloseButtonPressed() { OnCloseButtonPressed.Broadcast(); }

protected:
	virtual void NativeOnInitialized();

	const FString MaxLevelText = "Max";
	const FString CloseText = "Close";

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BuildingText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> CloseButton;

	// ==================================================
	//           Upgrade
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> UpgradeButton;

	// ==================================================
	//           Demolish
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> DemolishButton;

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
