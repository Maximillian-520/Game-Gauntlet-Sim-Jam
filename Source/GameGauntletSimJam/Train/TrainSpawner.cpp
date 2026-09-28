#include "TrainSpawner.h"

ATrainSpawner::ATrainSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATrainSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATrainSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

ATrain* ATrainSpawner::SpawnTrain()
{
    if (!TrainBlueprint) return nullptr;

    if (UWorld* World = GetWorld())
    {
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        ATrain* TrainInstance = World->SpawnActor<ATrain>(TrainBlueprint, SpawnLocation, SpawnRotation, SpawnParams);

        return TrainInstance;
    }
    else return nullptr;
}

