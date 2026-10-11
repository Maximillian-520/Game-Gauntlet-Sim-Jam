#include "GameManager.h"

void UGameManager::GameLost()
{
	UGameplayStatics::SetGamePaused(this, true);
	OnGameLost.Broadcast();
}
