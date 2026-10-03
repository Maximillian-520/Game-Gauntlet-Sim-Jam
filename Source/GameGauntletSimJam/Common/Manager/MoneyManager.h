#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MoneyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMoneyChanged, int32, NewAmount, int32, Delta);

UCLASS()
class UMoneyManager : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintPure, Category = "Money")
    int32 GetMoney() const { return Money; }

    UFUNCTION(BlueprintPure, Category = "Money")
    bool CanAfford(int32 Amount) const { return Money >= Amount; }

    UFUNCTION(BlueprintCallable, Category = "Money")
    void SetMoney(int32 Amount);

    UFUNCTION(BlueprintCallable, Category = "Money")
    void AddMoney(int32 Amount);

    // Returns false (and changes nothing) if the player can't afford it
    UFUNCTION(BlueprintCallable, Category = "Money")
    bool TrySpend(int32 Amount);

    UPROPERTY(BlueprintAssignable, Category = "Money")
    FOnMoneyChanged OnMoneyChanged;

private:
    int32 Money = 0;
};