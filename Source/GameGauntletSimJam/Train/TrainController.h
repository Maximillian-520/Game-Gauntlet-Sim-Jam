#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainSpawner.h"
#include "../Customer/CustomerSpawner.h"
#include "TrainController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATrainController : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrainController();

	// ==================================================
	//           Controller
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	ATrainSpawner* TrainSpawner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	ACustomerSpawner* CustomerSpawner;

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void CreateIncomingTrain();

	// ==================================================
	//           Incoming Train Flow
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IncomingTrainFlow")
	ATargetPoint* DisembarkPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IncomingTrainFlow")
	ATargetPoint* DisappearPoint;
	
	UFUNCTION(BlueprintCallable, Category = "IncomingTrainFlow")
	void DisembrakTrain();

	UFUNCTION(BlueprintCallable, Category = "IncomingTrainFlow")
	void ToDisappearLocation();

	UFUNCTION(BlueprintCallable, Category = "IncomingTrainFlow")
	void DisappearTrain();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	ATrain* CurrentTrain;

	FTimerHandle DelayTimerHandle;
};
