#include "TrainViewModel.h"

void UTrainViewModel::Initialize(ATrainController* InController)
{
	Controller = InController;

	Controller->OnNotificationRequested.AddDynamic(this, &UTrainViewModel::HandleNotificationRequested);
}