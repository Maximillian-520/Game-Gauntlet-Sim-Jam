#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "GameManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameLost);

UCLASS()
class UGameManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Game")
	void GameLost();

	UPROPERTY(BlueprintAssignable, Category = "Game")
	FOnGameLost OnGameLost;
};
