#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "../../Train/TrainController.h"
#include "TrainViewModel.generated.h"

UCLASS(BlueprintType)
class GAMEGAUNTLETSIMJAM_API UTrainViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(ATrainController* InController);

	UFUNCTION()
	void HandleNotificationRequested(
		const FText& TrainType, const FText& TrainName, const FText& Message
	)
	{
		BroadcastOnNotificationRequested(TrainType, TrainName, Message);
	}

	UFUNCTION()
	void HandleNotificationDeleted(const FText& TrainName)
	{
		BroadcastOnNotificationDeleted(TrainName);
	}

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

private:
	TWeakObjectPtr<ATrainController> Controller;

};