#pragma once

#include "CoreMinimal.h"
// Custom
#include "../BaseBuilding.h"
#include "../../Common/Manager/TrackerManager.h"
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

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void Tick(float DeltaTime) override;

	void UpdateTrackIntervalReduction();

	float CalculateTrackIntervalReduction() const;

private:
	float CurrentTrackIntervalReduction;
};
