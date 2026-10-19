#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Components/BoxComponent.h"
#include "../BaseBuilding.h"
#include "Plot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlotClicked, APlot*, Plot);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingChanged, ABaseBuilding*, NewBuilding);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBuildingDestoryed);

UCLASS()
class GAMEGAUNTLETSIMJAM_API APlot : public AActor
{
	GENERATED_BODY()
	
public:	
	APlot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plot")
	int32 PlotNumber = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plot")
	ABaseBuilding* Building = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Plot")
	bool HasBuilding() const { return Building != nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Plot")
	bool CanBuild(TSubclassOf<ABaseBuilding> BuildingClass) const;

	UFUNCTION(BlueprintCallable, Category = "Plot")
	ABaseBuilding* BuildBuilding(TSubclassOf<ABaseBuilding> BuildingBlueprint);

	UFUNCTION(BlueprintCallable, Category = "Plot")
	void UpgradeBuilding();

	UFUNCTION(BlueprintCallable, Category = "Plot")
	void DemolishBuilding();

	UPROPERTY(BlueprintAssignable, Category = "Plot")
	FOnPlotClicked OnPlotClicked;
	UFUNCTION(BlueprintImplementableEvent, Category = "Plot")
	void OnPlotClickedBP();

	UPROPERTY(BlueprintAssignable, Category = "Plot")
	FOnBuildingChanged OnBuildingChanged;
	UFUNCTION(BlueprintImplementableEvent, Category = "Plot")
	void OnBuildingChangedBP();

	UPROPERTY(BlueprintAssignable, Category = "Plot")
	FOnBuildingDestoryed OnBuildingDestoryed;
	UFUNCTION(BlueprintImplementableEvent, Category = "Plot")
	void OnBuildingDestoryedBP();

protected:
	virtual void NotifyActorOnClicked(FKey ButtonPressed) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plot")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plot")
	TObjectPtr<USceneComponent> BuildingRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Plot")
	TObjectPtr<UBoxComponent> ClickArea;

	UFUNCTION(BlueprintCallable)
	void DestroyBuilding();

	void SetPlot();

private:
	ABaseBuilding* DestoryedBuilding = nullptr;
};
