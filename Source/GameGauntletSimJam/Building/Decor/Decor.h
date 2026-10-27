#pragma once

#include "CoreMinimal.h"
// Custom
#include "../BaseBuilding.h"
#include "../../Common/Manager/CustomerManager.h"
// ==========
#include "Decor.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ADecor : public ABaseBuilding
{
	GENERATED_BODY()
	
public:	
	ADecor();
	
	virtual void Upgrade();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decor")
	TArray<float> SpawnIntervalReductions = TArray<float>{ 0.1 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decor")
	TArray<float> InterestedChanceIncreases = TArray<float>{ 0.0 };

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void Tick(float DeltaTime) override;

	void UpdateBuildingEffect();

	float CalculateSpawnIntervalReduction() const;

	float CalculateInterestedChanceIncrease() const;

private:
	UPROPERTY()
	UCustomerManager* CustomerManager = nullptr;

	float CurrentSpawnIntervalReduction;
	float CurrentInterestedChanceIncrease;
};
