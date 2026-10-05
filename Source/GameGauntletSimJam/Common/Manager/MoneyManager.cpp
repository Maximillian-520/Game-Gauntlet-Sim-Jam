#include "MoneyManager.h"

void UMoneyManager::Reset(int32 InitialMoney)
{
    Money = InitialMoney;
    OnMoneyChanged.Broadcast(Money, 0);
}

void UMoneyManager::SetMoney(int32 Amount)
{
    if (Amount <= 0) return;

    int32 PrevAmount = Money;
    Money = Amount;
    OnMoneyChanged.Broadcast(Money, Amount - PrevAmount);
}

void UMoneyManager::AddMoney(int32 Amount)
{
    if (Amount <= 0) return;

    Money += Amount;
    OnMoneyChanged.Broadcast(Money, Amount);
}

bool UMoneyManager::TrySpend(int32 Amount)
{
    if (Amount <= 0 || !CanAfford(Amount)) return false;

    Money -= Amount;
    OnMoneyChanged.Broadcast(Money, -Amount);
    return true;
}