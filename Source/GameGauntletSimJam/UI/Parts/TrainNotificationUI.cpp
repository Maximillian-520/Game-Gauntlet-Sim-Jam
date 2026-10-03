#include "TrainNotificationUI.h"

void UTrainNotificationUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (MessageText) MessageText->SetText(NotificationMessage);

	if (FadeAnim) PlayAnimation(FadeAnim, 0.f, 1, EUMGSequencePlayMode::Forward);

	GetWorld()->GetTimerManager().SetTimer(
		DisappearTimer, this, &UTrainNotificationUI::Disappear, NotificationDuration, false);
}

void UTrainNotificationUI::NativeDestruct()
{
	if (UWorld* World = GetWorld()) World->GetTimerManager().ClearTimer(DisappearTimer);

	Super::NativeDestruct();
}

void UTrainNotificationUI::Disappear()
{
	if (FadeAnim)
	{
		bIsMarkedForDestoy = true;
		PlayAnimation(FadeAnim, 0.f, 1, EUMGSequencePlayMode::Reverse);
	}
	else RemoveFromParent();
}