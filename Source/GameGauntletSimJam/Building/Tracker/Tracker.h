#pragma once

#include "CoreMinimal.h"
// Custom
#include "../BaseBuilding.h"
#include "../../Common/Manager/TrainManager.h"
// ==========
#include "Tracker.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATracker : public ABaseBuilding
{
	GENERATED_BODY()
	
public:
	ATracker();

	virtual void Upgrade();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracker")
	TArray<float> TrackIntervalReductions = TArray<float>{ 1.5 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracker")
	TArray<float> SpawnIntervalIncreases = TArray<float>{ 0.0 };

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void Tick(float DeltaTime) override;

	void UpdateBuildingEffect();

	float CalculateTrackIntervalReduction() const;

	float CalculateSpawnIntervalIncrease() const;

private:
	UPROPERTY()
	UTrainManager* TrainManager = nullptr;

	float CurrentTrackIntervalReduction;
	float CurrentSpawnIntervalIncrease;
};
