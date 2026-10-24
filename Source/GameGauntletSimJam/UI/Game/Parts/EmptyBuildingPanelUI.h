#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
// Custom
#include "../../Component/BasicButton.h"
#include "../../../Building/BaseBuilding.h"
#include "../../../Common/Manager/MoneyManager.h"
// ==========
#include "EmptyBuildingPanelUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildButtonPressed, TSubclassOf<ABaseBuilding>, BuildingBlueprint);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UEmptyBuildingPanelUI : public UUserWidget
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseButtonPressed);

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Show(int32 PlotNumber);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Hide();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdatePanel();

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnBuildButtonPressed OnBuildButtonPressed;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnCloseButtonPressed OnCloseButtonPressed;
	UFUNCTION()
	void BroadcastOnCloseButtonPressed() { OnCloseButtonPressed.Broadcast(); }

protected:
	virtual void NativeOnInitialized();

	const FString CloseText = "Close";

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> BuildingText;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> CloseButton;

	// ==================================================
	//           Shop
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> BuildShopButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ABaseBuilding> ShopBlueprint;

	// ==================================================
	//           Tracker
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> BuildTrackerButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ABaseBuilding> TrackerBlueprint;

	// ==================================================
	//           Decor
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> BuildDecorButton;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	TSubclassOf<ABaseBuilding> DecorBlueprint;

	// ==================================================
	//           Event
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleBuildShopButtonPressed() { OnBuildButtonPressed.Broadcast(ShopBlueprint); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleBuildTrackerButtonPressed() { OnBuildButtonPressed.Broadcast(TrackerBlueprint); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleBuildDecorButtonPressed() { OnBuildButtonPressed.Broadcast(DecorBlueprint); }

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleMoneyChanged(int32 NewAmount, int32 Delta) { UpdatePanel(); }

private:
	UMoneyManager* MoneyManager;

	int32 ShopCost;
	int32 TrackerCost;
	int32 DecorCost;
};
