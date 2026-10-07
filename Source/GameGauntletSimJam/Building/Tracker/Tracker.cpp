#include "Tracker.h"

ATracker::ATracker()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void ATracker::BeginPlay()
{
	Super::BeginPlay();

	UpdateTrackIntervalReduction();
}

//void ATracker::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ATracker::Upgrade()
{
	Super::Upgrade();

	SetBuildingLevelMesh();
}

void ATracker::UpdateTrackIntervalReduction()
{
	float NewTrackIntervalReduction = CalculateTrackIntervalReduction();
	float OffsetTrackIntervalReduction = NewTrackIntervalReduction - CurrentTrackIntervalReduction;

	CurrentTrackIntervalReduction = NewTrackIntervalReduction;

	if (UTrackerManager* TrackerManager = UGameInstance::GetSubsystem<UTrackerManager>(GetGameInstance()))
	{
		TrackerManager->AddTrackIntervalReduction(OffsetTrackIntervalReduction);
	}
}

float ATracker::CalculateTrackIntervalReduction()
{
	return BaseTrackIntervalReduction + (TrackIntervalReductionPerLevel * FMath::Max(0, GetCurrentLevel()));
}
