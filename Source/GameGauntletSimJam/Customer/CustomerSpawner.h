#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Customer.h"
#include "CustomerSpawner.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerSpawner();

	// ==================================================
	//           Spawner
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<ACustomer> CustomerBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<ATargetPoint*> SpawnPoints;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnCustomer();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnCustomerAtInterval(int Amount, float DelayInterval);
	
	// ==================================================
	//           Customer
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customer")
	ATargetPoint* ExitPoint;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	// Spawn at interval
	bool bSpawnAtIntervalActive;
	FTimerHandle SpawnAtIntervalTimerHandle;
	int SpawnAtIntervalTargetAmount;
	int SpawnAtIntervalCurrentAmount;

};
