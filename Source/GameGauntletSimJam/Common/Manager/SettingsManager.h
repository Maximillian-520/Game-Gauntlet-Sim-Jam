#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/GameUserSettings.h"
#include "AudioDevice.h"
#include "Engine/Engine.h"
#include "Misc/ConfigCacheIni.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "SettingsManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVolumeChanged, float, NewVolume);

/**
 * Owns the game's audio settings (music + SFX volume), persists them to
 * GameUserSettings.ini and pushes them to the audio engine via a SoundMix.
 *
 * Set this in Config/DefaultGame.ini:
 *
 *   [/Script/GAMEGAUNTLETSIMJAM.SettingsManager]
 *   SettingsSoundMix=/Game/Audio/SCM_MainAudioMix.SCM_MainAudioMix
 *   MusicSoundClass=/Game/Audio/SC_Music.SC_Music
 *   SfxSoundClass=/Game/Audio/SC_SFX.SC_SFX
 */
UCLASS(Config = Game, DefaultConfig)
class GAMEGAUNTLETSIMJAM_API USettingsManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetMusicVolume() const { return MusicVolume; }

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetSfxVolume() const { return SfxVolume; }

	/** Volumes are clamped to [0, 1]. */
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMusicVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSfxVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ResetToDefaults();

	/** Writes the current values to disk. Call when the user finishes editing. */
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void LoadSettings();

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnVolumeChanged OnMusicVolumeChanged;

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnVolumeChanged OnSfxVolumeChanged;

	static constexpr float DefaultMusicVolume = 0.8f;
	static constexpr float DefaultSfxVolume = 1.0f;

protected:
	UPROPERTY(Config)
	TSoftObjectPtr<USoundMix> SettingsSoundMix;

	UPROPERTY(Config)
	TSoftObjectPtr<USoundClass> MusicSoundClass;

	UPROPERTY(Config)
	TSoftObjectPtr<USoundClass> SfxSoundClass;

private:
	float MusicVolume = DefaultMusicVolume;
	float SfxVolume = DefaultSfxVolume;
	
	void ApplyAudio() const;
	void ApplyClassVolume(USoundMix* Mix, USoundClass* SoundClass, float Volume) const;

	void SetupScalability();
};
