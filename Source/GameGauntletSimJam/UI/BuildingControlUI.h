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

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> BuildShopButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> CloseButton;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> CostText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Build")
	TSubclassOf<ABaseBuilding> ShopBlueprint;

private:
	UPROPERTY()
	TObjectPtr<UBuildingViewModel> ViewModel;

	UFUNCTION()
	void HandlePlotSelected();

	UFUNCTION()
	void HandleBuildShop();
};
