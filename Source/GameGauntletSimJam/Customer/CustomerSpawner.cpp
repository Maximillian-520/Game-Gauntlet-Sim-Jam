#include "CustomerSpawner.h"

ACustomerSpawner::ACustomerSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerSpawner::BeginPlay()
{
	Super::BeginPlay();
}

void ACustomerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomerSpawner::SpawnCustomer()
{
    if (!CustomerBlueprint) return;

    // --- Spawn customer ---
    if (UWorld* World = GetWorld())
    {
        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();

        // Pick a random spawn point if any are set
        if (SpawnPoints.Num() > 0)
        {
            int32 RandomIndex = FMath::RandRange(0, SpawnPoints.Num() - 1);
            if (ATargetPoint* ChosenPoint = SpawnPoints[RandomIndex])
            {
                SpawnLocation = ChosenPoint->GetActorLocation();
                SpawnRotation = ChosenPoint->GetActorRotation();
            }
        }

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        ACustomer* CustomerInstance = World->SpawnActor<ACustomer>(CustomerBlueprint, SpawnLocation, SpawnRotation, SpawnParams);

        if (CustomerInstance && ExitPoint) CustomerInstance->SetExitLocation(ExitPoint->GetActorLocation());
    }

    // --- Check spawn at interval ---
    if (bSpawnAtIntervalActive)
    {
        SpawnAtIntervalCurrentAmount++;
        if (SpawnAtIntervalCurrentAmount >= SpawnAtIntervalTargetAmount)
        {
            bSpawnAtIntervalActive = false;
            if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(SpawnAtIntervalTimerHandle);
        }
    }
}

void ACustomerSpawner::SpawnCustomerAtInterval(int Amount, float Interval)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(
            SpawnAtIntervalTimerHandle,
            this,
            &ACustomerSpawner::SpawnCustomer,
            Interval,
            true // loop
        );
    }
    bSpawnAtIntervalActive = true;
    SpawnAtIntervalTargetAmount = Amount;
    SpawnAtIntervalCurrentAmount = 0;
}
