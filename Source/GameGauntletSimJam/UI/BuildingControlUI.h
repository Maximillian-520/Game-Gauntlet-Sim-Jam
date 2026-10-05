#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "./ViewModel/BuildingViewModel.h"
#include "../Building/BaseBuilding.h"
#include "BuildingControlUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UBuildingControlUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Show();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Hide();

protected:
	virtual void NativeOnInitialized() override;

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	// ==================================================
	//           Shop
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BuildShopButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> ShopCostText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI|Build")
	TSubclassOf<ABaseBuilding> ShopBlueprint;

	// ==================================================
	//           Tracker
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BuildTrackerButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> TrackerCostText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI|Build")
	TSubclassOf<ABaseBuilding> TrackerBlueprint;


private:
	UPROPERTY()
	TObjectPtr<UBuildingViewModel> ViewModel;

	UFUNCTION()
	void HandlePlotSelected();

	UFUNCTION()
	void HandleBuildShop();

	UFUNCTION()
	void HandleBuildTracker();
};
