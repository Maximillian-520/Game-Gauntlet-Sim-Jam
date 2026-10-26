#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "Engine/GameInstance.h"
// Custom
#include "../../Component/BasicButton.h"
#include "../../ViewModel/SettingsViewModel.h"
#include "../../../Common/Manager/SettingsManager.h"
// ==========
#include "SettingsUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSettingsCloseRequested);

UCLASS()
class GAMEGAUNTLETSIMJAM_API USettingsUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Fired when CloseButton is clicked; the owner decides how to hide the screen. */
	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnSettingsCloseRequested OnCloseRequested;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> MusicSlider;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<USlider> SfxSlider;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> MusicValueText;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> SfxValueText;

	UPROPERTY(meta = (BindWidgetOptional))
	UBasicButton* ResetButton;

	UPROPERTY(meta = (BindWidgetOptional))
	UBasicButton* CloseButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText ResetButtonText = FText::FromString("Reset");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FText CloseButtonText = FText::FromString("Close");

private:
	UFUNCTION()
	void HandleMusicSliderChanged(float Value);

	UFUNCTION()
	void HandleSfxSliderChanged(float Value);

	UFUNCTION()
	void HandleSliderCaptureEnd();

	UFUNCTION()
	void HandleResetClicked();

	UFUNCTION()
	void HandleCloseClicked();

	// Driven by the view model (so reset / external changes update the sliders).
	UFUNCTION()
	void HandleMusicVolumeChanged(float NewVolume);

	UFUNCTION()
	void HandleSfxVolumeChanged(float NewVolume);

	void RefreshMusic(float Volume);
	void RefreshSfx(float Volume);

	UPROPERTY()
	TObjectPtr<USettingsViewModel> ViewModel;
};
