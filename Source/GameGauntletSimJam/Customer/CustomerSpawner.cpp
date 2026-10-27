#include "CustomerSpawner.h"

ACustomerSpawner::ACustomerSpawner()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomerSpawner::BeginPlay()
{
	Super::BeginPlay();

    if (bStartSpawningImmediately) StartSpawning();
}

void ACustomerSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (bIsSpawning)
    {
        SpawnTimer -= DeltaTime;

        if (SpawnTimer <= 0)
        {
            SpawnCustomer();
            ResetSpawnTimer();
        }
    }
}

// ==================================================
//           Spawner
// ==================================================

void ACustomerSpawner::StartSpawning()
{
    bIsSpawning = true;
    ResetSpawnTimer();
}

void ACustomerSpawner::StopSpawning()
{
    bIsSpawning = false;
}

void ACustomerSpawner::SpawnCustomer()
{
    if (!CustomerBlueprint) return;

    // --- Spawn customer ---

    if (UWorld* World = GetWorld())
    {
        // --- Pick a random spawn area and a random location to spawn ---

        FVector SpawnLocation = GetActorLocation();
        FRotator SpawnRotation = GetActorRotation();
        int32 SpawnAreaIndex = INDEX_NONE;

        // Pick a random spawn area if any are set
        if (SpawnAreas.Num() > 0)
        {
            SpawnAreaIndex = FMath::RandRange(0, SpawnAreas.Num() - 1);
            if (ATriggerBox* ChosenArea = SpawnAreas[SpawnAreaIndex])
            {
                UBoxComponent* Box = Cast<UBoxComponent>(ChosenArea->GetCollisionComponent());
                if (Box) SpawnLocation = GetRandomPointInArea(Box);
                SpawnRotation = ChosenArea->GetActorRotation();
            }
        }

        AActor* ExitActor = this;
        FVector ExitLocation = GetActorLocation();
        FRotator ExitRotation = GetActorRotation();

        // --- Pick a random exit from any other spawn area ---

        TArray<UBoxComponent*> ExitCandidates;

        for (int32 i = 0; i < SpawnAreas.Num(); ++i)
        {
            if (i == SpawnAreaIndex) continue;
            if (ATriggerBox* Area = SpawnAreas[i])
            {
                if (UBoxComponent* Box = Cast<UBoxComponent>(Area->GetCollisionComponent())) ExitCandidates.Add(Box);
            }
        }

        if (ExitCandidates.Num() > 0)
        {
            // Get random exit
            UBoxComponent* ExitBox = ExitCandidates[FMath::RandRange(0, ExitCandidates.Num() - 1)];
            // Set exit location
            ExitLocation = GetRandomPointInArea(ExitBox);
            // Set exit rotation
            ExitRotation = ExitBox->GetOwner()->GetActorRotation();
            ExitRotation.Yaw += 180.f;
            ExitRotation.Normalize();
        }

        // --- Spawn and set new instance ---

        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        ACustomer* CustomerInstance = World->SpawnActor<ACustomer>(CustomerBlueprint, SpawnLocation, SpawnRotation, SpawnParams);

        if (CustomerInstance)
        {
            // Set parent
            if (CustomerInstanceParent)
            {
                CustomerInstance->AttachToActor(
                    CustomerInstanceParent,
                    FAttachmentTransformRules::KeepWorldTransform
                );
            }
            // Set exit
            CustomerInstance->SetExit(ExitActor, ExitLocation, ExitRotation);
            // Set interested and purchase chance
            CustomerInstance->InterestedChance = FMath::Min(
                1.0f, CustomerInstance->InterestedChance + InterestedChanceIncreaseModifier
            );
            CustomerInstance->PurchaseChance = FMath::Min(
                1.0f, CustomerInstance->PurchaseChance + PurchaseChanceIncreaseModifier
            );
            // Broadcast event
            OnCustomerSpawned.Broadcast(CustomerInstance);
        }
    }
}

UBoxComponent* ACustomerSpawner::GetNearestSpawnArea(const FVector CurrentLocation)
{
    UBoxComponent* NearestBox = nullptr;
    float NearestDistSq = TNumericLimits<float>::Max();

    for (ATriggerBox* Area : SpawnAreas)
    {
        if (!Area) continue;

        UBoxComponent* Box = Cast<UBoxComponent>(Area->GetCollisionComponent());
        if (!Box) continue;

        // Squared distance to the box surface (0 if the location is inside it)
        float DistSq = 0.f;
        FVector ClosestPoint;

        if (!Box->GetSquaredDistanceToCollision(CurrentLocation, DistSq, ClosestPoint))
        {
            // No valid collision on the component, fall back to center distance
            DistSq = FVector::DistSquared(CurrentLocation, Box->GetComponentLocation());
        }

        if (DistSq < NearestDistSq)
        {
            NearestDistSq = DistSq;
            NearestBox = Box;
        }
    }

    return NearestBox;
}

FVector ACustomerSpawner::GetRandomPointInArea(const UBoxComponent* Area) const
{
    if (!Area) return GetActorLocation();

    const FVector Extent = Area->GetUnscaledBoxExtent();

    // Random point in the local X/Y plane (Z = 0 keeps it flat)
    const FVector LocalPoint(
        FMath::FRandRange(-Extent.X, Extent.X),
        FMath::FRandRange(-Extent.Y, Extent.Y),
        0.f);

    // Converts to world space, respecting the component's location, rotation and scale
    return Area->GetComponentTransform().TransformPosition(LocalPoint);
}

void ACustomerSpawner::ResetSpawnTimer()
{
    const float MinInterval = FMath::Max(0.0f, FMath::Min(MinSpawnInterval, MaxSpawnInterval));
    const float MaxInterval = FMath::Max(MinSpawnInterval, MaxSpawnInterval);

    SpawnTimer = FMath::FRandRange(MinInterval, MaxInterval);
}
