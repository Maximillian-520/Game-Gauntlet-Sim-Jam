#include "SettingsUI.h"

void USettingsUI::NativeConstruct()
{
	Super::NativeConstruct();

	USettingsManager* SettingsManager = nullptr;
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		SettingsManager = GameInstance->GetSubsystem<USettingsManager>();
	}

	ViewModel = NewObject<USettingsViewModel>(this);
	ViewModel->Initialize(SettingsManager);
	ViewModel->OnMusicVolumeChanged.AddDynamic(this, &USettingsUI::HandleMusicVolumeChanged);
	ViewModel->OnSfxVolumeChanged.AddDynamic(this, &USettingsUI::HandleSfxVolumeChanged);

	MusicSlider->SetMinValue(0.f);
	MusicSlider->SetMaxValue(1.f);
	SfxSlider->SetMinValue(0.f);
	SfxSlider->SetMaxValue(1.f);

	MusicSlider->OnValueChanged.AddDynamic(this, &USettingsUI::HandleMusicSliderChanged);
	SfxSlider->OnValueChanged.AddDynamic(this, &USettingsUI::HandleSfxSliderChanged);
	MusicSlider->OnMouseCaptureEnd.AddDynamic(this, &USettingsUI::HandleSliderCaptureEnd);
	SfxSlider->OnMouseCaptureEnd.AddDynamic(this, &USettingsUI::HandleSliderCaptureEnd);

	if (ResetButton)
	{
		ResetButton->OnButtonClicked.AddDynamic(this, &USettingsUI::HandleResetClicked);
		ResetButton->SetButtonText(ResetButtonText);
	}
	if (CloseButton)
	{
		CloseButton->OnButtonClicked.AddDynamic(this, &USettingsUI::HandleCloseClicked);
		CloseButton->SetButtonText(CloseButtonText);
	}

	// Show the current values.
	RefreshMusic(ViewModel->GetMusicVolume());
	RefreshSfx(ViewModel->GetSfxVolume());
}

void USettingsUI::NativeDestruct()
{
	if (MusicSlider)
	{
		MusicSlider->OnValueChanged.RemoveDynamic(this, &USettingsUI::HandleMusicSliderChanged);
		MusicSlider->OnMouseCaptureEnd.RemoveDynamic(this, &USettingsUI::HandleSliderCaptureEnd);
	}
	if (SfxSlider)
	{
		SfxSlider->OnValueChanged.RemoveDynamic(this, &USettingsUI::HandleSfxSliderChanged);
		SfxSlider->OnMouseCaptureEnd.RemoveDynamic(this, &USettingsUI::HandleSliderCaptureEnd);
	}
	if (ResetButton)
	{
		ResetButton->OnButtonClicked.RemoveDynamic(this, &USettingsUI::HandleResetClicked);
	}
	if (CloseButton)
	{
		CloseButton->OnButtonClicked.RemoveDynamic(this, &USettingsUI::HandleCloseClicked);
	}

	if (ViewModel)
	{
		// Make sure anything changed with the keyboard / gamepad is saved.
		ViewModel->Commit();
		ViewModel->OnMusicVolumeChanged.RemoveDynamic(this, &USettingsUI::HandleMusicVolumeChanged);
		ViewModel->OnSfxVolumeChanged.RemoveDynamic(this, &USettingsUI::HandleSfxVolumeChanged);
		ViewModel->Deinitialize();
		ViewModel = nullptr;
	}

	Super::NativeDestruct();
}

void USettingsUI::HandleMusicSliderChanged(float Value)
{
	if (ViewModel) ViewModel->SetMusicVolume(Value);
}

void USettingsUI::HandleSfxSliderChanged(float Value)
{
	if (ViewModel) ViewModel->SetSfxVolume(Value);
}

void USettingsUI::HandleSliderCaptureEnd()
{
	if (ViewModel) ViewModel->Commit();
}

void USettingsUI::HandleResetClicked()
{
	if (ViewModel)
	{
		ViewModel->ResetToDefaults();
		ViewModel->Commit();
	}
}

void USettingsUI::HandleCloseClicked()
{
	if (ViewModel) ViewModel->Commit();
	OnCloseRequested.Broadcast();
}

void USettingsUI::HandleMusicVolumeChanged(float NewVolume)
{
	RefreshMusic(NewVolume);
}

void USettingsUI::HandleSfxVolumeChanged(float NewVolume)
{
	RefreshSfx(NewVolume);
}

void USettingsUI::RefreshMusic(float Volume)
{
	// SetValue doesn't re-fire OnValueChanged, so there's no feedback loop.
	if (MusicSlider && !FMath::IsNearlyEqual(MusicSlider->GetValue(), Volume))
	{
		MusicSlider->SetValue(Volume);
	}
	if (MusicValueText)
	{
		MusicValueText->SetText(FText::AsPercent(Volume));
	}
}

void USettingsUI::RefreshSfx(float Volume)
{
	if (SfxSlider && !FMath::IsNearlyEqual(SfxSlider->GetValue(), Volume))
	{
		SfxSlider->SetValue(Volume);
	}
	if (SfxValueText)
	{
		SfxValueText->SetText(FText::AsPercent(Volume));
	}
}