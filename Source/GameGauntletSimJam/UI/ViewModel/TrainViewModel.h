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
	void HandleNotificationRequested(const FText& Message) { BroadcastOnNotification(Message); }

	UPROPERTY(BlueprintAssignable)
	FOnNotificationRequested OnNotificationRequested;
	void BroadcastOnNotification(const FText& Message) { OnNotificationRequested.Broadcast(Message); }

private:
	TWeakObjectPtr<ATrainController> Controller;

};