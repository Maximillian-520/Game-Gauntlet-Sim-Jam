#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

UCLASS(Abstract)
class GAMEGAUNTLETSIMJAM_API ABaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBuilding();

	// ==================================================
	//           Building
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	FText BuildingName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	int32 BuildCost = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Building")
	TArray<TSubclassOf<AActor>> BuildingLevelBlueprints;

	// ==================================================
	//           Upgrade
	// ==================================================
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Upgrade")
	int32 MaxLevel = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Upgrade")
	TArray<int32> UpgradeCosts = TArray<int32>{ 100 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Upgrade")
	TArray<FText> UpgradeDescriptions = TArray<FText>{ FText::FromString("Upgrading")};

	UFUNCTION(BlueprintCallable, Category = "Building|Upgrade")
	virtual void Upgrade();

	UFUNCTION(BlueprintPure, Category = "Building|Upgrade")
	int32 GetUpgradeCost() const;

	UFUNCTION(BlueprintPure, Category = "Building|Upgrade")
	FText GetUpgradeDescription() const;

	UFUNCTION(BlueprintPure, Category = "Building|Upgrade")
	int32 GetCurrentLevel() const { return Level; }

	UFUNCTION(BlueprintPure, Category = "Building|Upgrade")
	bool IsMaxLevel() const { return Level >= MaxLevel; }

	// ==================================================
	//           Demolish
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building|Demolish",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float DemolishValueMargin = 0.5f;

	UFUNCTION(BlueprintPure, Category = "Building|Demolish")
	int32 GetDemolishValue() const;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// ==================================================
	//           Building
	// ==================================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Building")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, Category = "Building")
	int32 Level = 1;

	void SetBuildingLevelMesh();

private:
	UPROPERTY()
	TObjectPtr<AActor> CurrentBuildingLevelMesh = nullptr;
};
