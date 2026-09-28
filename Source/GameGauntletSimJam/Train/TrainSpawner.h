#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Train.h"
#include "TrainSpawner.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATrainSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrainSpawner();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<ATrain> TrainBlueprint;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	ATrain* SpawnTrain();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
