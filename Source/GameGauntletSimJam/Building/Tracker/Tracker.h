#pragma once

#include "CoreMinimal.h"
#include "../BaseBuilding.h"
#include "../../Common/Manager/TrackerManager.h"
#include "Tracker.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATracker : public ABaseBuilding
{
	GENERATED_BODY()
	
public:
	ATracker();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracker")
	float BaseTrackIntervalReduction = 1.0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tracker")
	float TrackIntervalReductionPerLevel = 0.5;

	virtual void Upgrade();

protected:
	virtual void BeginPlay() override;
	
	//virtual void Tick(float DeltaTime) override;

	void UpdateTrackIntervalReduction();

	float CalculateTrackIntervalReduction();

private:
	float CurrentTrackIntervalReduction;
};
