#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "../ViewModel/BuildingViewModel.h"
#include "./Parts/BuildingPanelUI.h"
#include "./Parts/EmptyBuildingPanelUI.h"
#include "../../Building/BaseBuilding.h"
#include "../../Common/Manager/GameManager.h"
#include "BuildingControlUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UBuildingControlUI : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UBuildingPanelUI> BuildingPanel;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UEmptyBuildingPanelUI> EmptyBuildingPanel;

	UPROPERTY()
	TObjectPtr<UBuildingViewModel> ViewModel;

	UFUNCTION()
	void HandlePlotSelected();

	UFUNCTION()
	void HandleBuildButtonPressed(TSubclassOf<ABaseBuilding> BuildingBlueprint);

	UFUNCTION()
	void HandleUpgradeButtonPressed();

	UFUNCTION()
	void HandleDemolishButtonPressed();

	UFUNCTION()
	void HandleCloseButtonPressed();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnShowBP();

	UFUNCTION(BlueprintImplementableEvent, Category = "Event")
	void OnHideBP();

private:
	bool bIsShown = false;

	UPROPERTY()
	UGameManager* GameManager = nullptr;

	UFUNCTION()
	void HandleGameUIShown() { SetVisibility(ESlateVisibility::Visible); }

	UFUNCTION()
	void HandleGameUIHidden() { SetVisibility(ESlateVisibility::Hidden); }
};
