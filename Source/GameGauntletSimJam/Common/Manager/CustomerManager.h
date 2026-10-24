#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomerManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSpawnIntervalChanged);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UCustomerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    const float MinimumSpawnInterval = 0.05f;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void Reset(float InitialBaseSpawnInterval = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    float GetCalculatedSpawnInterval() const;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void AddSpawnIntervalReduction(float Reduction);

    UPROPERTY(BlueprintAssignable, Category = "Spawning")
    FOnSpawnIntervalChanged OnSpawnIntervalChanged;

private:
    float BaseSpawnInterval = 3.0f;
    float SpawnIntervalReduction = 0.0f;
};
