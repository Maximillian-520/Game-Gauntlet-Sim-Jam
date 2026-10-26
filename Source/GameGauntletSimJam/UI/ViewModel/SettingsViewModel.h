#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
// Custom
#include "../../Common/Manager/SettingsManager.h"
// ==========
#include "SettingsViewModel.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API USettingsViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(USettingsManager* InManager);
	void Deinitialize();

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetMusicVolume() const;

	UFUNCTION(BlueprintPure, Category = "Settings")
	float GetSfxVolume() const;

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetMusicVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void SetSfxVolume(float NewVolume);

	UFUNCTION(BlueprintCallable, Category = "Settings")
	void ResetToDefaults();

	/** Persist the current values to disk. */
	UFUNCTION(BlueprintCallable, Category = "Settings")
	void Commit();

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnVolumeChanged OnMusicVolumeChanged;
	UFUNCTION()
	void BroadcastMusicVolumeChanged(float NewVolume) { OnMusicVolumeChanged.Broadcast(NewVolume); }

	UPROPERTY(BlueprintAssignable, Category = "Settings")
	FOnVolumeChanged OnSfxVolumeChanged;
	UFUNCTION()
	void BroadcastSfxVolumeChanged(float NewVolume) { OnSfxVolumeChanged.Broadcast(NewVolume); }

private:
	UPROPERTY()
	TObjectPtr<USettingsManager> SettingsManager;
};
