#include "LoseUI.h"

void ULoseUI::NativeConstruct()
{
    Super::NativeConstruct();

    GameManager = UGameInstance::GetSubsystem<UGameManager>(GetGameInstance());
    if (!GameManager) return;

    GameManager->OnGameLost.AddDynamic(this, &ULoseUI::ShowUI);
    RestartButton->OnButtonClicked.AddDynamic(this, &ULoseUI::HandleRestartClicked);
    QuitButton->OnButtonClicked.AddDynamic(this, &ULoseUI::HandleQuitClicked);

    RestartButton->SetButtonText(FText::FromString(RestartText));
    QuitButton->SetButtonText(FText::FromString(QuitText));

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
    if (GameManager) GameManager->RestartGame();
}

void ULoseUI::HandleQuitClicked()
{
    if (GameManager) GameManager->QuitGame();
}