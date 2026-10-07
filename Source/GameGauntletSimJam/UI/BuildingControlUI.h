#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "./ViewModel/BuildingViewModel.h"
#include "./Parts/BuildingPanelUI.h"
#include "./Parts/EmptyBuildingPanelUI.h"
#include "../Building/BaseBuilding.h"
#include "BuildingControlUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UBuildingControlUI : public UUserWidget
{
	GENERATED_BODY()

public:

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuildingPanelUI> BuildingPanel;

	UPROPERTY(meta = (BindWidget))
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

private:
};
