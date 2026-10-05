#include "TrackerManager.h"

void UTrackerManager::Reset(float InitialBaseTrackInterval)
{
    BaseTrackInterval = InitialBaseTrackInterval;
    TrackIntervalReduction = 0.0f;
}

float UTrackerManager::GetCalculatedTrackInterval(int32 DivideCount)
{
    return FMath::Max(MinimumTrackInterval, BaseTrackInterval - (TrackIntervalReduction / DivideCount));
}

void UTrackerManager::AddTrackIntervalReduction(float Reduction)
{
    TrackIntervalReduction += Reduction;
    OnTrackIntervalChanged.Broadcast();
}
