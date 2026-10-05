#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TrackerManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrackIntervalChanged);

const float MinimumTrackInterval = 0.1f;

UCLASS()
class GAMEGAUNTLETSIMJAM_API UTrackerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Money")
    void Reset(float InitialBaseTrackInterval = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    float GetCalculatedTrackInterval(int32 DivideCount);

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    void AddTrackIntervalReduction(float Reduction);

    UPROPERTY(BlueprintAssignable, Category = "Tracking")
    FOnTrackIntervalChanged OnTrackIntervalChanged;

private:
    float BaseTrackInterval = 3.0f;
    float TrackIntervalReduction = 0.0f;
};
