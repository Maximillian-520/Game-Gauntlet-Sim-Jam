#include "SettingsManager.h"

namespace
{
	const TCHAR* SettingsSection = TEXT("GameSettings.Audio");
	const TCHAR* MusicKey = TEXT("MusicVolume");
	const TCHAR* SfxKey = TEXT("SfxVolume");
}

void USettingsManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	LoadSettings();
	ApplyAudio();
}

void USettingsManager::SetMusicVolume(float NewVolume)
{
	NewVolume = FMath::Clamp(NewVolume, 0.f, 1.f);
	if (FMath::IsNearlyEqual(MusicVolume, NewVolume)) return;

	MusicVolume = NewVolume;
	if (USoundMix* Mix = SettingsSoundMix.LoadSynchronous())
	{
		ApplyClassVolume(Mix, MusicSoundClass.LoadSynchronous(), MusicVolume);
	}
	OnMusicVolumeChanged.Broadcast(MusicVolume);
}

void USettingsManager::SetSfxVolume(float NewVolume)
{
	NewVolume = FMath::Clamp(NewVolume, 0.f, 1.f);
	if (FMath::IsNearlyEqual(SfxVolume, NewVolume)) return;

	SfxVolume = NewVolume;
	if (USoundMix* Mix = SettingsSoundMix.LoadSynchronous())
	{
		ApplyClassVolume(Mix, SfxSoundClass.LoadSynchronous(), SfxVolume);
	}
	OnSfxVolumeChanged.Broadcast(SfxVolume);
}

void USettingsManager::ResetToDefaults()
{
	SetMusicVolume(DefaultMusicVolume);
	SetSfxVolume(DefaultSfxVolume);
}

void USettingsManager::SaveSettings()
{
	if (!GConfig) return;

	GConfig->SetFloat(SettingsSection, MusicKey, MusicVolume, GGameUserSettingsIni);
	GConfig->SetFloat(SettingsSection, SfxKey, SfxVolume, GGameUserSettingsIni);
	GConfig->Flush(false, GGameUserSettingsIni);
}

void USettingsManager::LoadSettings()
{
	MusicVolume = DefaultMusicVolume;
	SfxVolume = DefaultSfxVolume;

	if (!GConfig) return;

	float Loaded = 0.f;
	if (GConfig->GetFloat(SettingsSection, MusicKey, Loaded, GGameUserSettingsIni))
	{
		MusicVolume = FMath::Clamp(Loaded, 0.f, 1.f);
	}
	if (GConfig->GetFloat(SettingsSection, SfxKey, Loaded, GGameUserSettingsIni))
	{
		SfxVolume = FMath::Clamp(Loaded, 0.f, 1.f);
	}
}

void USettingsManager::ApplyAudio() const
{
	USoundMix* Mix = SettingsSoundMix.LoadSynchronous();
	if (!Mix)
	{
		UE_LOG(LogTemp, Warning, TEXT("SettingsManager: SettingsSoundMix is not set in DefaultGame.ini; volumes will not be applied."));
		return;
	}

	if (FAudioDeviceHandle AudioDevice = GEngine ? GEngine->GetMainAudioDevice() : FAudioDeviceHandle())
	{
		AudioDevice->SetBaseSoundMix(Mix);
	}

	ApplyClassVolume(Mix, MusicSoundClass.LoadSynchronous(), MusicVolume);
	ApplyClassVolume(Mix, SfxSoundClass.LoadSynchronous(), SfxVolume);
}

void USettingsManager::ApplyClassVolume(USoundMix* Mix, USoundClass* SoundClass, float Volume) const
{
	if (!SoundClass) return;

	SoundClass->Properties.Volume = Volume;
}