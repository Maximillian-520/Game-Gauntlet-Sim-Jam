#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TrackerManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTrackIntervalChanged);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UTrackerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    const float MinimumTrackInterval = 0.1f;

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    void Reset(float InitialBaseTrackInterval = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    float GetCalculatedTrackInterval(int32 DivideCount) const;

    UFUNCTION(BlueprintCallable, Category = "Tracking")
    void AddTrackIntervalReduction(float Reduction);

    UPROPERTY(BlueprintAssignable, Category = "Tracking")
    FOnTrackIntervalChanged OnTrackIntervalChanged;

private:
    float BaseTrackInterval = 3.0f;
    float TrackIntervalReduction = 0.0f;
};
