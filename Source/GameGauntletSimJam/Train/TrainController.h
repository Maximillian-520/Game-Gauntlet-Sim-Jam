#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainSpawner.h"
#include "TrainController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNotificationRequested, const FText&, TrainName, const FText&, Message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotificationDeleted, const FText&, TrainName);

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATrainController : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrainController();

	// ==================================================
	//           Reference
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	ATrainSpawner* TrainSpawner;

	// ==================================================
	//           Controller
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	int32 MaxTrainCount = 1;

	UPROPERTY(BlueprintAssignable)
	FOnNotificationRequested OnNotificationRequested;
	void BroadcastOnNotificationRequested(const FText& TrainName, const FText& Message)
	{
		OnNotificationRequested.Broadcast(TrainName, Message);
	}

	UPROPERTY(BlueprintAssignable)
	FOnNotificationDeleted OnNotificationDeleted;
	void BroadcastOnNotificationDeleted(const FText& TrainName)
	{
		OnNotificationDeleted.Broadcast(TrainName); 
	}

	// ==================================================
	//           Event
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleTrainSpawned(ATrain* Train);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleTrainTravelUpdate(ATrain* Train);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleTrainArrived(ATrain* Train);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleTrainHitCustomer(ACustomer* HitCustomer);

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleTrainDestroyed(AActor* DestroyedActor);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// ==================================================
	//           Controller
	// ==================================================

	FText GetFormatedDistanceText(float Distance);

private:
	UPROPERTY(VisibleAnywhere, Category = "Controller")
	int32 TrainCount = 0;

	TArray<ATrain*> Trains;

};
