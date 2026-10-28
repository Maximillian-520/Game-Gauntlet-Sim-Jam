#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUIShown);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameUIHidden);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLost);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameResumed);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGamePaused);

UCLASS()
class UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	// ==================================================
	//           Flow
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Flow")
	FName GameLevelName = TEXT("GameMap");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Flow")
	FName MenuLevelName = TEXT("MenuMap");

	UFUNCTION(BlueprintCallable, Category = "Game|Flow")
	void StartGame();
	
	UFUNCTION(BlueprintCallable, Category = "Game|Flow")
	void LoseGame();

	UFUNCTION(BlueprintCallable, Category = "Game|Flow")
	void RestartGame();

	UFUNCTION(BlueprintCallable, Category = "Game|Flow")
	void QuitGame();

	UFUNCTION(BlueprintCallable, Category = "Game|Pausing")
	bool IsGameRunning() const { return bIsGameRunning; }

	UFUNCTION(BlueprintCallable, Category = "Game|Pausing")
	bool IsGameLost() const { return bIsGameLost; }

	UPROPERTY(BlueprintAssignable, Category = "Game|Flow")
	FOnGameUIShown OnGameUIShown;

	UPROPERTY(BlueprintAssignable, Category = "Game|Flow")
	FOnGameUIHidden OnGameUIHidden;

	UPROPERTY(BlueprintAssignable, Category = "Game|Flow")
	FOnGameLost OnGameLost;

	// ==================================================
	//           Pausing
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Game|Pausing")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category = "Game|Pausing")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Game|Pausing")
	bool IsGamePaused() const { return bIsGamePaused; }

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnGameResumed OnGameResumed;

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnGamePaused OnGamePaused;

private:
	bool bIsGameRunning = false;
	bool bIsGamePaused = false;
	bool bIsGameLost = false;
};
