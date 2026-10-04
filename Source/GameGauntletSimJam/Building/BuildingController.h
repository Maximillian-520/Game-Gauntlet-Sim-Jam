#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./Plot/Plot.h"
#include "BuildingController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ABuildingController : public AActor
{
	GENERATED_BODY()

public:
	ABuildingController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	TArray<APlot*> Plots;

	UPROPERTY(BlueprintAssignable, Category = "Building")
	FOnPlotClicked OnPlotClicked;

	UFUNCTION()
	void BuildOnPlot(APlot* Plot, TSubclassOf<ABaseBuilding> BuildingBlueprint);

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void HandlePlotClicked(APlot* Plot) { OnPlotClicked.Broadcast(Plot); }

};