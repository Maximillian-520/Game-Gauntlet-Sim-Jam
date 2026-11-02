#include "MenuUI.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	// --- Connect events ---

	StartButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Start);
	TutorialButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Tutorial);
	SettingsButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Settings);
	QuitButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Quit);
	CreditsButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Credits);

	TutorialCloseButton->OnButtonClicked.AddDynamic(this, &UMenuUI::HandleTutorialCloseClicked);
	SettingsUI->OnCloseRequested.AddDynamic(this, &UMenuUI::HandleSettingsCloseRequested);
	CreditsCloseButton->OnButtonClicked.AddDynamic(this, &UMenuUI::HandleCreditsCloseClicked);

	// --- Initialize ---
	
	StartButton->SetButtonText(StartButtonText);
	TutorialButton->SetButtonText(TutorialButtonText);
	SettingsButton->SetButtonText(SettingsButtonText);
	QuitButton->SetButtonText(QuitButtonText);
	CreditsButton->SetButtonText(CreditsButtonText);

	TutorialCloseButton->SetButtonText(TutorialCloseButtonText);
	CreditsCloseButton->SetButtonText(CreditsCloseButtonText);

	MainPanel->SetVisibility(ESlateVisibility::Visible);
	TutorialPanel->SetVisibility(ESlateVisibility::Collapsed);
	SettingsUI->SetVisibility(ESlateVisibility::Collapsed);
	CreditsPanel->SetVisibility(ESlateVisibility::Collapsed);
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

void UMenuUI::Credits()
{
	MainPanel->SetVisibility(ESlateVisibility::Collapsed);
	CreditsPanel->SetVisibility(ESlateVisibility::Visible);
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

void UMenuUI::HandleCreditsCloseClicked()
{
	MainPanel->SetVisibility(ESlateVisibility::Visible);
	CreditsPanel->SetVisibility(ESlateVisibility::Collapsed);
}