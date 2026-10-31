#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/PanelWidget.h"
// Custom
#include "../Component/BasicButton.h"
#include "./Parts/SettingsUI.h"
// ==========
#include "MenuUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Level opened when Start is pressed. Set this in the widget Blueprint's class defaults. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	FName GameLevelName = TEXT("GameMap");

protected:
	virtual void NativeConstruct() override;

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* MainPanel;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* TutorialButton;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* SettingsButton;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* QuitButton;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* CreditsButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Main")
	FText StartButtonText = FText::FromString("Start");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Main")
	FText TutorialButtonText = FText::FromString("How to Play");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Main")
	FText SettingsButtonText = FText::FromString("Settings");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Main")
	FText QuitButtonText = FText::FromString("Quit");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Main")
	FText CreditsButtonText = FText::FromString("Credits");

	// ==================================================
	//           Tutorial
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* TutorialPanel;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* TutorialCloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Tutorial")
	FText TutorialCloseButtonText = FText::FromString("Close");

	// ==================================================
	//           Settings
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	USettingsUI* SettingsUI;

	// ==================================================
	//           Credits
	// ==================================================

	UPROPERTY(meta = (BindWidget))
	UPanelWidget* CreditsPanel;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* CreditsCloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|Credits")
	FText CreditsCloseButtonText = FText::FromString("Close");

private:
	UFUNCTION()
	void Start();

	UFUNCTION()
	void Tutorial();

	UFUNCTION()
	void Settings();

	UFUNCTION()
	void Quit();

	UFUNCTION()
	void Credits();

	UFUNCTION()
	void HandleTutorialCloseClicked();

	UFUNCTION()
	void HandleSettingsCloseRequested();

	UFUNCTION()
	void HandleCreditsCloseClicked();
};
