#include "TrainNotificationUI.h"

void UTrainNotificationUI::Show(const FText& TrainType, const FText& TrainName, const FText& Status)
{
	if (IncomingTrainText) IncomingTrainText->SetText(
		FText::Format(INVTEXT("Incoming {0}: {1}"), TrainType, TrainName)
	);

	if (StatusText) StatusText->SetText(Status);
}

void UTrainNotificationUI::Update(const FText& Status)
{
	if (StatusText) StatusText->SetText(Status);
	OnNotificationUpdate.Broadcast();
}

void UTrainNotificationUI::Disappear()
{
	if (bHasDisappearAnimation) OnNotificationDisappear.Broadcast();
	else RemoveFromParent();
}