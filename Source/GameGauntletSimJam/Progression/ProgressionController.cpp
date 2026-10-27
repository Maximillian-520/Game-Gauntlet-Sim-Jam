#include "ProgressionController.h"

AProgressionController::AProgressionController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AProgressionController::BeginPlay()
{
	Super::BeginPlay();
	
	TrainManager = UGameInstance::GetSubsystem<UTrainManager>(GetGameInstance());
	if (!TrainManager) UE_LOG(LogTemp, Warning, TEXT("TrainManager did not exist"));

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
		float TrainSpawnInterval = TrainSpawnIntervalCurve->GetFloatValue(ElapsedGameTimer);
		if (TrainManager) TrainSpawnInterval += TrainManager->GetSpawnIntervalIncrease();

		TrainSpawner->MinSpawnInterval = TrainSpawnInterval;
		TrainSpawner->MaxSpawnInterval = TrainSpawnInterval;
	}

	// Update Train Travel Duration
	if (TrainTravelDurationCurve)
	{
		TrainSpawner->OverrideTravelDurationValue = TrainTravelDurationCurve->GetFloatValue(ElapsedGameTimer);
	}
}

