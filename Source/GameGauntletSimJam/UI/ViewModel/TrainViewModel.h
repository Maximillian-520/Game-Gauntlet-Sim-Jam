#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
// Custom
#include "../../Train/TrainController.h"
// ==========
#include "TrainViewModel.generated.h"

UCLASS(BlueprintType)
class GAMEGAUNTLETSIMJAM_API UTrainViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(ATrainController* InController);

	UPROPERTY(BlueprintAssignable)
	FOnNotificationRequested OnNotificationRequested;
	UFUNCTION()
	void BroadcastOnNotificationRequested(
		const FText& TrainType, const FText& TrainName, const FText& Message
	)
	{
		OnNotificationRequested.Broadcast(TrainType, TrainName, Message);
	}

	UPROPERTY(BlueprintAssignable)
	FOnNotificationDeleted OnNotificationDeleted;
	UFUNCTION()
	void BroadcastOnNotificationDeleted(const FText& TrainName)
	{
		OnNotificationDeleted.Broadcast(TrainName);
	}

private:
	TWeakObjectPtr<ATrainController> Controller;

};