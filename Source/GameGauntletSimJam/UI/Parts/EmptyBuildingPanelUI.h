#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../../Building/BaseBuilding.h"
#include "../../Common/Manager/MoneyManager.h"
#include "EmptyBuildingPanelUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildButtonPressed, TSubclassOf<ABaseBuilding>, BuildingBlueprint);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UEmptyBuildingPanelUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Show(int32 PlotNumber);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Hide();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdatePanel();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnBuildButtonPressed OnBuildButtonPressed;

protected:
	virtual void NativeOnInitialized();

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BuildingText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// ==================================================
	//           Shop
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BuildShopButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ShopCostText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ABaseBuilding> ShopBlueprint;

	// ==================================================
	//           Tracker
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BuildTrackerButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TrackerCostText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ABaseBuilding> TrackerBlueprint;

	// ==================================================
	//           Event
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleBuildShopButtonPressed() { OnBuildButtonPressed.Broadcast(ShopBlueprint); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleBuildTrackerButtonPressed() { OnBuildButtonPressed.Broadcast(TrackerBlueprint); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleMoneyChanged(int32 NewAmount, int32 Delta) { UpdatePanel(); }

private:
	UMoneyManager* MoneyManager;

	int32 ShopCost;
	int32 TrackerCost;
};
