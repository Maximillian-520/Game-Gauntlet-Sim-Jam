#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Train.h"
#include "TrainSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainSpawned, ATrain*, Train);

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATrainSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrainSpawner();

	// ==================================================
	//           Spawner
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<ATrain> TrainBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	ATargetPoint* FirstEndPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	ATargetPoint* LastEndPoint;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StopSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnTrain();

	UPROPERTY(BlueprintAssignable, Category = "Spawner")
	FOnTrainSpawned OnTrainSpawned;

	// ==================================================
	//           Settings
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bStartSpawningImmediately = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bIsSpawning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MinSpawnInterval = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxSpawnInterval = 10.0f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	float SpawnTimer;

	void ResetSpawnTimer();

};
