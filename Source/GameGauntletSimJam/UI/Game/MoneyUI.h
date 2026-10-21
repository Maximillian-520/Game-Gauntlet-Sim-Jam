#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
#include "TimerManager.h"
#include "../../Common/Manager/MoneyManager.h"
#include "../../Common/Manager/GameManager.h"
#include "MoneyUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UMoneyUI : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    virtual void NativeDestruct() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* MoneyText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
    UTextBlock* DeltaText;

    UFUNCTION(BlueprintImplementableEvent, Category = "Money")
    void OnMoneyChangedBP(int32 NewAmount, int32 Delta);

private:
    UPROPERTY()
    UMoneyManager* MoneyManager = nullptr;

    UPROPERTY()
    UGameManager* GameManager = nullptr;

    UFUNCTION()
    void HandleMoneyChanged(int32 NewAmount, int32 Delta);

    UFUNCTION()
    void HandleGameUIShown() { SetVisibility(ESlateVisibility::Visible); }

    UFUNCTION()
    void HandleGameUIHidden() { SetVisibility(ESlateVisibility::Hidden); }

    void UpdateMoneyText(int32 Amount);
};