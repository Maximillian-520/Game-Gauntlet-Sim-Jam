#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TrainManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrackIntervalChanged);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UTrainManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    // ==================================================
    //           Tracking
    // ==================================================
    
    const float MinimumTrackInterval = 0.1f;

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    void Reset(float InitialBaseTrackInterval = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    float GetCalculatedTrackInterval(int32 DivideCount) const;

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    void AddTrackIntervalReduction(float Reduction);

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    void AddTrackerBuildingCount(int Count);

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    bool CanTrackTrains() const { return TrackerBuildingCount > 0; }

    UPROPERTY(BlueprintAssignable, Category = "Tracking")
    FOnTrackIntervalChanged OnTrackIntervalChanged;

    // ==================================================
    //           Spawning
    // ==================================================

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void AddSpawnIntervalIncrease(float Increase);

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    float GetSpawnIntervalIncrease() { return SpawnIntervalIncrease; }

private:
    // Tracking
    float BaseTrackInterval = 3.0f;
    float TrackIntervalReduction = 0.0f;
    int32 TrackerBuildingCount = 0;

    // Spawning
    float SpawnIntervalIncrease = 0.0f;
};
