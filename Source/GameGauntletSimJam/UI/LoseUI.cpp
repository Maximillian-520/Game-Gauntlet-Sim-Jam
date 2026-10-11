#include "LoseUI.h"

void ULoseUI::NativeConstruct()
{
    Super::NativeConstruct();

    GameManager = UGameInstance::GetSubsystem<UGameManager>(GetGameInstance());
    if (!GameManager) return;

    GameManager->OnGameLost.AddDynamic(this, &ULoseUI::ShowUI);
    if (RestartButton) RestartButton->OnClicked.AddDynamic(this, &ULoseUI::HandleRestartClicked);
    if (QuitButton) QuitButton->OnClicked.AddDynamic(this, &ULoseUI::HandleQuitClicked);

    HideUI();
}

void ULoseUI::ShowUI()
{
    SetVisibility(ESlateVisibility::Visible);
}

void ULoseUI::HideUI()
{
    SetVisibility(ESlateVisibility::Collapsed);
}

void ULoseUI::HandleRestartClicked()
{
    const FName LevelName = FName(*UGameplayStatics::GetCurrentLevelName(this));
    UGameplayStatics::OpenLevel(this, LevelName);
}

void ULoseUI::HandleQuitClicked()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}