#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Custom
#include "TrainSpawner.h"
#include "../Common/Manager/GameManager.h"
#include "../Common/Manager/TrainManager.h"
// ==========
#include "TrainController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(
	FOnNotificationRequested, const FText&, TrainType, const FText&, TrainName, const FText&, Status
);
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

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void UpdateTrainTrackInterval();

	UPROPERTY(BlueprintAssignable)
	FOnNotificationRequested OnNotificationRequested;
	void BroadcastOnNotificationRequested(
		const FText& TrainType, const FText& TrainName, const FText& Message
	)
	{
		OnNotificationRequested.Broadcast(TrainType, TrainName, Message);
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

	UFUNCTION(BlueprintCallable, Category = "Event")
	void HandleTrackIntervalChanged() { UpdateTrainTrackInterval(); }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// ==================================================
	//           Controller
	// ==================================================

	FText GetFormatedDistanceText(float Distance);

	void CheckTrainPassQueue();

private:
	UPROPERTY()
	UGameManager* GameManager = nullptr;
	UPROPERTY()
	UTrainManager* TrainManager = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Controller")
	int32 TrainCount = 0;
	TArray<ATrain*> Trains;

	ATrain* CurrentTrainPassing;
	TArray<ATrain*> TrainPassQueue;

};
