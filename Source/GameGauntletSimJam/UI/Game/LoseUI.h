#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Component/BasicButton.h"
#include "../../Common/Manager/GameManager.h"
#include "LoseUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ULoseUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
    UFUNCTION()
    void ShowUI();

    UFUNCTION()
    void HideUI();

protected:
    virtual void NativeConstruct() override;

    const FString RestartText = "Restart";
    const FString QuitText = "Quit";

    UPROPERTY(meta = (BindWidget))
    UBasicButton* RestartButton;

    UPROPERTY(meta = (BindWidget))
    UBasicButton* QuitButton;

    UFUNCTION()
    void HandleRestartClicked();

    UFUNCTION()
    void HandleQuitClicked();

private:
	UPROPERTY()
	UGameManager* GameManager = nullptr;
};
