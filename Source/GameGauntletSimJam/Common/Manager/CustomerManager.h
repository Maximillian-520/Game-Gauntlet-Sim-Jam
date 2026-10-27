#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "CustomerManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCustomerStatChanged);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UCustomerManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    // ==================================================
    //           Spawning
    // ==================================================

    const float MinimumSpawnInterval = 0.05f;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void Reset(float InitialBaseSpawnInterval = 3.0f);

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    float GetCalculatedSpawnInterval() const;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void AddSpawnIntervalReduction(float Reduction);

    UPROPERTY(BlueprintAssignable, Category = "Spawning")
    FOnCustomerStatChanged OnSpawnIntervalChanged;

    // ==================================================
    //           Interested
    // ==================================================

    UFUNCTION(BlueprintCallable, Category = "Interested")
    void AddInterestedChanceIncrease(float Increase);

    UFUNCTION(BlueprintCallable, Category = "Interested")
    float GetInterestedChanceIncrease() const { return InterestedChanceIncrease; }

    UPROPERTY(BlueprintAssignable, Category = "Spawning")
    FOnCustomerStatChanged OnInterestedChanceChanged;

private:
    // Spawning
    float BaseSpawnInterval = 3.0f;
    float SpawnIntervalReduction = 0.0f;

    // Interested
    float InterestedChanceIncrease = 0.0f;
};
