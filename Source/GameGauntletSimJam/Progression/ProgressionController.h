#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Custom
#include "../Train/TrainController.h"
#include "../Train/TrainSpawner.h"
#include "../Common/Manager/TrainManager.h"
// ==========
#include "ProgressionController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AProgressionController : public AActor
{
	GENERATED_BODY()
	
public:	
	AProgressionController();

	// ==================================================
	//           Reference
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	ATrainController* TrainController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	ATrainSpawner* TrainSpawner;

	// ==================================================
	//           Progression
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	float DifficultyUpdateInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	UCurveFloat* MaxTrainCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	UCurveFloat* TrainSpawnIntervalCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Progression")
	UCurveFloat* TrainTravelDurationCurve;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void UpdateDifficulty();

private:
	UPROPERTY()
	UTrainManager* TrainManager = nullptr;

	float DifficultyUpdateTimer = 0.0;
	float ElapsedGameTimer = 0.0;
};
