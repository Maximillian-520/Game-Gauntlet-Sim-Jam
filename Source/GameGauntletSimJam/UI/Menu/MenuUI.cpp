#include "MenuUI.h"

void UMenuUI::NativeConstruct()
{
	Super::NativeConstruct();

	StartButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Start);
	QuitButton->OnButtonClicked.AddDynamic(this, &UMenuUI::Quit);

	StartButton->SetButtonText(FText::FromString(StartText));
	QuitButton->SetButtonText(FText::FromString(QuitText));
}

void UMenuUI::Start()
{
	RemoveFromParent();
	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UMenuUI::Quit()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, false);
}