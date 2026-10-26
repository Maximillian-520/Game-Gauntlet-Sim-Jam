#include "SettingsViewModel.h"

void USettingsViewModel::Initialize(USettingsManager* InManager)
{
	Deinitialize();

	SettingsManager = InManager;
	if (SettingsManager)
	{
		SettingsManager->OnMusicVolumeChanged.AddDynamic(this, &USettingsViewModel::BroadcastMusicVolumeChanged);
		SettingsManager->OnSfxVolumeChanged.AddDynamic(this, &USettingsViewModel::BroadcastSfxVolumeChanged);
	}
}

void USettingsViewModel::Deinitialize()
{
	if (SettingsManager)
	{
		SettingsManager->OnMusicVolumeChanged.RemoveDynamic(this, &USettingsViewModel::BroadcastMusicVolumeChanged);
		SettingsManager->OnSfxVolumeChanged.RemoveDynamic(this, &USettingsViewModel::BroadcastSfxVolumeChanged);
		SettingsManager = nullptr;
	}
}

float USettingsViewModel::GetMusicVolume() const
{
	return SettingsManager ? SettingsManager->GetMusicVolume() : USettingsManager::DefaultMusicVolume;
}

float USettingsViewModel::GetSfxVolume() const
{
	return SettingsManager ? SettingsManager->GetSfxVolume() : USettingsManager::DefaultSfxVolume;
}

void USettingsViewModel::SetMusicVolume(float NewVolume)
{
	if (SettingsManager)
	{
		SettingsManager->SetMusicVolume(NewVolume);
	}
}

void USettingsViewModel::SetSfxVolume(float NewVolume)
{
	if (SettingsManager) SettingsManager->SetSfxVolume(NewVolume);
}

void USettingsViewModel::ResetToDefaults()
{
	if (SettingsManager) SettingsManager->ResetToDefaults();
}

void USettingsViewModel::Commit()
{
	if (SettingsManager) SettingsManager->SaveSettings();
}