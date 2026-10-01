#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MoneyUI.generated.h"

class UTextBlock;
class UMoneyManager;

UCLASS()
class GAMEGAUNTLETSIMJAM_API UMoneyUI : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual void NativeConstruct() override;

    virtual void NativeDestruct() override;

    // Must exist in the Widget Blueprint with exactly this name
    UPROPERTY(meta = (BindWidget))
    UTextBlock* MoneyText;

    // Optional: shows "+50" / "-20" briefly after a change
    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* DeltaText;

    UPROPERTY(EditDefaultsOnly, Category = "Money")
    FText Prefix = FText::FromString(TEXT("$"));

    UPROPERTY(EditDefaultsOnly, Category = "Money")
    float DeltaDisplayTime = 1.5f;

    // Lets you add animations/sounds in the Blueprint
    UFUNCTION(BlueprintImplementableEvent, Category = "Money")
    void OnMoneyChangedBP(int32 NewAmount, int32 Delta);

private:
    UFUNCTION()
    void HandleMoneyChanged(int32 NewAmount, int32 Delta);

    void UpdateMoneyText(int32 Amount);

    void HideDeltaText();

    UPROPERTY()
    UMoneyManager* MoneyManager = nullptr;

    FTimerHandle DeltaTimer;
};