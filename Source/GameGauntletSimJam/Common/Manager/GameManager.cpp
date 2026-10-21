#include "GameManager.h"

void UGameManager::LoseGame()
{
	UGameplayStatics::SetGamePaused(this, true);
	bIsGamePaused = false;

	bIsGameLost = true;

	OnGameUIHidden.Broadcast();
	OnGameLost.Broadcast();
}

void UGameManager::RestartGame()
{
	UGameplayStatics::SetGamePaused(this, false);
	bIsGamePaused = false;

	bIsGameLost = false;

	UGameplayStatics::OpenLevel(this, GameLevelName);
}

void UGameManager::QuitGame()
{
	UGameplayStatics::SetGamePaused(this, false);
	bIsGamePaused = false;

	bIsGameLost = false;

	UGameplayStatics::OpenLevel(this, MenuLevelName);
}

void UGameManager::ResumeGame()
{
	UGameplayStatics::SetGamePaused(this, false);
	bIsGamePaused = false;

	OnGameUIShown.Broadcast();
	OnGameResumed.Broadcast();
}

void UGameManager::PauseGame()
{
	UGameplayStatics::SetGamePaused(this, true);
	bIsGamePaused = true;

	OnGameUIHidden.Broadcast();
	OnGamePaused.Broadcast();
}
