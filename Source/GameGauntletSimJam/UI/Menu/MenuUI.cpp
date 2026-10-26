#include "MenuUI.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	// --- Connect events ---

	StartButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Start);
	TutorialButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Tutorial);
	SettingsButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Settings);
	QuitButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Quit);

	TutorialCloseButton->OnButtonClicked.AddDynamic(this, &UMenuUI::HandleTutorialCloseClicked);

	SettingsUI->OnCloseRequested.AddDynamic(this, &UMenuUI::HandleSettingsCloseRequested);

	// --- Initialize ---
	
	StartButton->SetButtonText(StartButtonText);
	TutorialButton->SetButtonText(TutorialButtonText);
	SettingsButton->SetButtonText(SettingsButtonText);
	QuitButton->SetButtonText(QuitButtonText);

	TutorialCloseButton->SetButtonText(TutorialCloseButtonText);

	MainPanel->SetVisibility(ESlateVisibility::Visible);
	TutorialPanel->SetVisibility(ESlateVisibility::Collapsed);
	SettingsUI->SetVisibility(ESlateVisibility::Collapsed);
}

void UMenuUI::Start()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UMenuUI::Tutorial()
{
	MainPanel->SetVisibility(ESlateVisibility::Collapsed);
	TutorialPanel->SetVisibility(ESlateVisibility::Visible);
}

void UMenuUI::Settings()
{
	MainPanel->SetVisibility(ESlateVisibility::Collapsed);
	SettingsUI->SetVisibility(ESlateVisibility::Visible);
}

void UMenuUI::Quit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}

void UMenuUI::HandleTutorialCloseClicked()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
	TutorialPanel->SetVisibility(ESlateVisibility::Collapsed);
}

void UMenuUI::HandleSettingsCloseRequested()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
	SettingsUI->SetVisibility(ESlateVisibility::Collapsed);
}