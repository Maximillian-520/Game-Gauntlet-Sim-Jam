#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "../../Building/BuildingController.h"
#include "BuildingViewModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlotSelected);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UBuildingViewModel : public UObject
{
	GENERATED_BODY()

public:
	void Initialize(ABuildingController* InController);

	void BuildRequested(TSubclassOf<ABaseBuilding> BuildingBlueprint);

	void UpgradeRequested();

	void DemolishRequested();
	
	APlot* GetSelectedPlot() const { return SelectedPlot; }

	UPROPERTY(BlueprintAssignable, Category = "Building")
	FOnPlotSelected OnPlotSelected;

private:
	TWeakObjectPtr<ABuildingController> Controller;

	UPROPERTY()
	APlot* SelectedPlot;

	UFUNCTION()
	void HandlePlotClicked(APlot* Plot);
};