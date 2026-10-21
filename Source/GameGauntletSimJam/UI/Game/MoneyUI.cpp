#include "MoneyUI.h"

void UMoneyUI::NativeConstruct()
{
    Super::NativeConstruct();

    MoneyManager = UGameInstance::GetSubsystem<UMoneyManager>(GetGameInstance());
    if (MoneyManager) MoneyManager->OnMoneyChanged.AddDynamic(this, &UMoneyUI::HandleMoneyChanged);

    GameManager = UGameInstance::GetSubsystem<UGameManager>(GetGameInstance());
    if (GameManager)
    {
        GameManager->OnGameUIShown.AddDynamic(this, &UMoneyUI::HandleGameUIShown);
        GameManager->OnGameUIHidden.AddDynamic(this, &UMoneyUI::HandleGameUIHidden);
    }

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
    }

    OnMoneyChangedBP(NewAmount, Delta);
}

void UMoneyUI::UpdateMoneyText(int32 Amount)
{
    if (MoneyText) MoneyText->SetText(FText::AsNumber(Amount));
}