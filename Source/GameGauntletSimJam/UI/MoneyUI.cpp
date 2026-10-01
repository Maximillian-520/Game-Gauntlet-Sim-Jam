#include "MoneyUI.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "TimerManager.h"
#include "../Common/MoneyManager.h"

void UMoneyUI::NativeConstruct()
{
    Super::NativeConstruct();

    MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());
    if (!MoneyManager) return;

    MoneyManager->OnMoneyChanged.AddDynamic(this, &UMoneyUI::HandleMoneyChanged);

    // Show the current value immediately
    UpdateMoneyText(MoneyManager->GetMoney());

    if (DeltaText) DeltaText->SetVisibility(ESlateVisibility::Collapsed);
}

void UMoneyUI::NativeDestruct()
{
    if (MoneyManager)
    {
        MoneyManager->OnMoneyChanged.RemoveDynamic(this, &UMoneyUI::HandleMoneyChanged);
        MoneyManager = nullptr;
    }

    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(DeltaTimer);
    }

    Super::NativeDestruct();
}

void UMoneyUI::HandleMoneyChanged(int32 NewAmount, int32 Delta)
{
    UpdateMoneyText(NewAmount);

    if (DeltaText && Delta != 0)
    {
        const FString Sign = Delta > 0 ? TEXT("+") : TEXT("-");
        DeltaText->SetText(FText::FromString(FString::Printf(TEXT("%s%d"), *Sign, FMath::Abs(Delta))));
        DeltaText->SetVisibility(ESlateVisibility::HitTestInvisible);

        GetWorld()->GetTimerManager().SetTimer(
            DeltaTimer, this, &UMoneyUI::HideDeltaText, DeltaDisplayTime, false);
    }

    OnMoneyChangedBP(NewAmount, Delta);
}

void UMoneyUI::UpdateMoneyText(int32 Amount)
{
    if (MoneyText)
    {
        MoneyText->SetText(FText::Format(
            FText::FromString(TEXT("{0}{1}")), Prefix, FText::AsNumber(Amount)));
    }
}

void UMoneyUI::HideDeltaText()
{
    if (DeltaText)
    {
        DeltaText->SetVisibility(ESlateVisibility::Collapsed);
    }
}