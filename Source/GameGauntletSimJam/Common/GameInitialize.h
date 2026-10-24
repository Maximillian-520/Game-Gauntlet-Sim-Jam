#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Custom
#include "Manager/MoneyManager.h"
#include "Manager/CustomerManager.h"
#include "Manager/TrackerManager.h"
// ==========
#include "GameInitialize.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AGameInitialize : public AActor
{
	GENERATED_BODY()
	
public:
	AGameInitialize();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize")
	float InitialMoney = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize")
	float BaseSpawnInterval = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Initialize")
	float BaseTrackInterval = 4.0f;

protected:
	virtual void BeginPlay() override;
};
