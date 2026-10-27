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
		FVector Value = TrainSpawnIntervalCurve->GetVectorValue(ElapsedGameTimer);
		float TrainMinSpawnInterval = Value.X;
		float TrainMaxSpawnInterval = Value.Y;
		if (TrainManager)
		{
			TrainMinSpawnInterval += TrainManager->GetSpawnIntervalIncrease();
			TrainMaxSpawnInterval += TrainManager->GetSpawnIntervalIncrease();
		}

		TrainSpawner->MinSpawnInterval = TrainMinSpawnInterval;
		TrainSpawner->MaxSpawnInterval = TrainMaxSpawnInterval;
	}

	// Update Train Travel Duration
	if (TrainTravelDurationCurve)
	{
		FVector Value = TrainTravelDurationCurve->GetVectorValue(ElapsedGameTimer);
		float TrainMinTravelDurationValue = Value.X;
		float TrainMaxTravelDurationValue = Value.Y;

		TrainSpawner->OverrideMinTravelDurationValue = TrainMinTravelDurationValue;
		TrainSpawner->OverrideMaxTravelDurationValue = TrainMaxTravelDurationValue;
	}
}

