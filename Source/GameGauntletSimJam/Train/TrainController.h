#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TrainSpawner.h"
#include "TrainController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNotificationRequested, const FText&, Message);

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATrainController : public AActor
{
	GENERATED_BODY()
	
public:	
	ATrainController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	ATrainSpawner* TrainSpawner;

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleTrainSpawned(ATrain* Train);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleTrainHitCustomer(ACustomer* HitCustomer);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleTrainDestroyed(AActor* DestroyedActor);

	UPROPERTY(BlueprintAssignable)
	FOnNotificationRequested OnNotificationRequested;
	void BroadcastOnNotification(const FText& Message) { OnNotificationRequested.Broadcast(Message); }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	TArray<ATrain*> Trains;

};
