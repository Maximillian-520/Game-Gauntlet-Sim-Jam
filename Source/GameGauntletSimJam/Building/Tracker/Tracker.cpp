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

void ATracker::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UTrackerManager* TrackerManager = UGameInstance::GetSubsystem<UTrackerManager>(GetGameInstance()))
	{
		TrackerManager->AddTrackIntervalReduction(-CalculateTrackIntervalReduction());
	}

	Super::EndPlay(EndPlayReason);
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

	UpdateTrackIntervalReduction();
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

float ATracker::CalculateTrackIntervalReduction() const
{
	if (TrackIntervalReductions.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, TrackIntervalReductions.Num());

	return TrackIntervalReductions[Index - 1];
}
