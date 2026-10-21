#include "PauseUI.h"

void UPauseUI::NativeConstruct()
{
    Super::NativeConstruct();

    GameManager = UGameInstance::GetSubsystem<UGameManager>(GetGameInstance());
    if (!GameManager) return;

    GameManager->OnGameResumed.AddDynamic(this, &UPauseUI::HideUI);
    GameManager->OnGamePaused.AddDynamic(this, &UPauseUI::ShowUI);
    ResumeButton->OnButtonClicked.AddDynamic(this, &UPauseUI::HandleResumeClicked);
    RestartButton->OnButtonClicked.AddDynamic(this, &UPauseUI::HandleRestartClicked);
    QuitButton->OnButtonClicked.AddDynamic(this, &UPauseUI::HandleQuitClicked);

    ResumeButton->SetButtonText(FText::FromString(ResumeText));
    RestartButton->SetButtonText(FText::FromString(RestartText));
    QuitButton->SetButtonText(FText::FromString(QuitText));

    HideUI();
}

void UPauseUI::ShowUI()
{
    SetVisibility(ESlateVisibility::Visible);
}

void UPauseUI::HideUI()
{
    SetVisibility(ESlateVisibility::Collapsed);
}

void UPauseUI::HandleResumeClicked()
{
    GameManager->ResumeGame();
    HideUI();
}

void UPauseUI::HandleRestartClicked()
{
    GameManager->RestartGame();
}

void UPauseUI::HandleQuitClicked()
{
    GameManager->QuitGame();
}