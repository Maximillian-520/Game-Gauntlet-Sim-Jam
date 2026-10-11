#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Common/Manager/GameManager.h"
#include "LoseUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ULoseUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual void NativeConstruct() override;

    UFUNCTION()
    void ShowUI();

    UFUNCTION()
    void HideUI();

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* RestartButton;

    UPROPERTY(meta = (BindWidget))
    UButton* QuitButton;

    UFUNCTION()
    void HandleRestartClicked();

    UFUNCTION()
    void HandleQuitClicked();

private:
	UPROPERTY()
	UGameManager* GameManager = nullptr;
};
