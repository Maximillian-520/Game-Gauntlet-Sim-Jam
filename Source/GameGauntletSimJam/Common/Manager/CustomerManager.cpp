#include "CustomerManager.h"

void UCustomerManager::Reset(float InitialBaseSpawnInterval)
{
    BaseSpawnInterval = InitialBaseSpawnInterval;
    SpawnIntervalReduction = 0.0f;
}

float UCustomerManager::GetCalculatedSpawnInterval() const
{
    return FMath::Max(MinimumSpawnInterval, BaseSpawnInterval - SpawnIntervalReduction);
}

void UCustomerManager::AddSpawnIntervalReduction(float Reduction)
{
    SpawnIntervalReduction += Reduction;
    OnSpawnIntervalChanged.Broadcast();
}