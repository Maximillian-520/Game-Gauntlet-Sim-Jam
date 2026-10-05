#include "TrainViewModel.h"

void UTrainViewModel::Initialize(ATrainController* InController)
{
	Controller = InController;

	Controller->OnNotificationRequested.AddDynamic(this, &UTrainViewModel::HandleNotificationRequested);
	Controller->OnNotificationDeleted.AddDynamic(this, &UTrainViewModel::HandleNotificationDeleted);
}