#include "ProgressionController.h"

AProgressionController::AProgressionController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AProgressionController::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateDifficulty();
	DifficultyUpdateTimer = DifficultyUpdateInterval;
}

void AProgressionController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DifficultyUpdateTimer -= DeltaTime;
	ElapsedGameTimer += DeltaTime;

	if (DifficultyUpdateTimer <= 0.0)
	{
		UpdateDifficulty();
		DifficultyUpdateTimer = DifficultyUpdateInterval;
	}
}

void AProgressionController::UpdateDifficulty()
{
	if (!TrainController || !TrainSpawner) return;


	// Update Max Train
	if (MaxTrainCurve)
	{
		TrainController->MaxTrainCount = MaxTrainCurve->GetFloatValue(ElapsedGameTimer);
	}

	// Update Train Spawn Interval
	if (TrainSpawnIntervalCurve)
	{
		TrainSpawner->MinSpawnInterval = TrainSpawnIntervalCurve->GetFloatValue(ElapsedGameTimer);
		TrainSpawner->MaxSpawnInterval = TrainSpawnIntervalCurve->GetFloatValue(ElapsedGameTimer);
	}

	// Update Train Travel Duration
	if (TrainTravelDurationCurve)
	{
		TrainSpawner->OverrideTravelDurationValue = TrainTravelDurationCurve->GetFloatValue(ElapsedGameTimer);
	}
}

