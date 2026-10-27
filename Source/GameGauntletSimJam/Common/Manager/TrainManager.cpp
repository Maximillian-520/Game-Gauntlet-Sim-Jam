#include "TrainManager.h"

// ==================================================
//           Tracking
// ==================================================

void UTrainManager::Reset(float InitialBaseTrackInterval)
{
    BaseTrackInterval = InitialBaseTrackInterval;
    TrackIntervalReduction = 0.0f;
}

float UTrainManager::GetCalculatedTrackInterval(int32 DivideCount) const
{
    return FMath::Max(MinimumTrackInterval, BaseTrackInterval - (TrackIntervalReduction / DivideCount));
}

void UTrainManager::AddTrackIntervalReduction(float Reduction)
{
    TrackIntervalReduction += Reduction;
    OnTrackIntervalChanged.Broadcast();
}

void UTrainManager::AddTrackerBuildingCount(int Count)
{
    TrackerBuildingCount += Count;
}

// ==================================================
//           Spawning
// ==================================================

void UTrainManager::AddSpawnIntervalIncrease(float Increase)
{
    SpawnIntervalIncrease += Increase;
}
