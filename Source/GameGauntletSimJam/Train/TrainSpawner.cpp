#include "TrainSpawner.h"

ATrainSpawner::ATrainSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATrainSpawner::BeginPlay()
{
    Super::BeginPlay();

    if (bStartSpawningImmediately) StartSpawning();
}

void ATrainSpawner::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsSpawning)
    {
        SpawnTimer -= DeltaTime;

        if (SpawnTimer <= 0)
        {
            SpawnTrain();
            ResetSpawnTimer();
        }
    }
}

void ATrainSpawner::StartSpawning()
{
    bIsSpawning = true;
    ResetSpawnTimer();
}

void ATrainSpawner::StopSpawning()
{
    bIsSpawning = false;
}

void ATrainSpawner::SpawnTrain()
{
    if (!TrainBlueprint) return;

    // --- Spawn train ---
    if (UWorld* World = GetWorld())
    {
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();
        FVector TargetLocation = GetActorLocation();

        // Pick either from first or last end to start
        if (FirstEndPoint && LastEndPoint)
        {
            if (FMath::RandRange(0, 1) == 0)
            {
                SpawnLocation = FirstEndPoint->GetActorLocation();
                SpawnRotation = FirstEndPoint->GetActorRotation();
                TargetLocation = LastEndPoint->GetActorLocation();
            }
            else
            {
                SpawnLocation = LastEndPoint->GetActorLocation();
                SpawnRotation = LastEndPoint->GetActorRotation();
                TargetLocation = FirstEndPoint->GetActorLocation();
            }
        }

        // --- Spawn and set new instance ---
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        ATrain* TrainInstance = World->SpawnActor<ATrain>(TrainBlueprint, SpawnLocation, SpawnRotation, SpawnParams);

        if (TrainInstance) 
        {
            TrainInstance->SetPassTargetLocation(TargetLocation);
            if (bOverrideTravelDurationOnSpawn) TrainInstance->OverrideTravelDuration(OverrideTravelDurationValue);
            OnTrainSpawned.Broadcast(TrainInstance);
        }
    }
}

void ATrainSpawner::ResetSpawnTimer()
{
    const float MinInterval = FMath::Max(0.0f, FMath::Min(MinSpawnInterval, MaxSpawnInterval));
    const float MaxInterval = FMath::Max(MinSpawnInterval, MaxSpawnInterval);

    SpawnTimer = FMath::FRandRange(MinInterval, MaxInterval);
}
