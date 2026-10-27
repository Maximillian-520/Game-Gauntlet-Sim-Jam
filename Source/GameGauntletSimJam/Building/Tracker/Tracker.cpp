#include "Tracker.h"

ATracker::ATracker()
{
	//PrimaryActorTick.bCanEverTick = true;
}

void ATracker::BeginPlay()
{
	Super::BeginPlay();

	TrainManager = UGameInstance::GetSubsystem<UTrainManager>(GetGameInstance());
	if (!TrainManager) UE_LOG(LogTemp, Warning, TEXT("TrainManager did not exist"));

	if (TrainManager) TrainManager->AddTrackerBuildingCount(1);

	UpdateBuildingEffect();
}

void ATracker::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TrainManager)
	{
		TrainManager->AddTrackerBuildingCount(-1);
		TrainManager->AddTrackIntervalReduction(-CurrentTrackIntervalReduction);
		TrainManager->AddSpawnIntervalIncrease(-CurrentSpawnIntervalIncrease);
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

	UpdateBuildingEffect();
}

void ATracker::UpdateBuildingEffect()
{
	// --- Update Track Interval Reduction ---

	float NewTrackIntervalReduction = CalculateTrackIntervalReduction();
	float OffsetTrackIntervalReduction = NewTrackIntervalReduction - CurrentTrackIntervalReduction;

	CurrentTrackIntervalReduction = NewTrackIntervalReduction;

	if (TrainManager) TrainManager->AddTrackIntervalReduction(OffsetTrackIntervalReduction);
	
	// --- Update Spawn Interval Increase ---
	
	float NewSpawnIntervalIncrease = CalculateSpawnIntervalIncrease();
	float OffsetSpawnIntervalIncrease = NewSpawnIntervalIncrease - CurrentSpawnIntervalIncrease;

	CurrentSpawnIntervalIncrease = NewSpawnIntervalIncrease;

	if (TrainManager) TrainManager->AddSpawnIntervalIncrease(OffsetSpawnIntervalIncrease);
}

float ATracker::CalculateTrackIntervalReduction() const
{
	if (TrackIntervalReductions.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, TrackIntervalReductions.Num());

	return TrackIntervalReductions[Index - 1];
}

float ATracker::CalculateSpawnIntervalIncrease() const
{
	if (SpawnIntervalIncreases.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, SpawnIntervalIncreases.Num());

	return SpawnIntervalIncreases[Index - 1];
}
