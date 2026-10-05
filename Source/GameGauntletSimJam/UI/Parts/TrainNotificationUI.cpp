#include "TrainNotificationUI.h"

void UTrainNotificationUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (FadeAnim) PlayAnimation(FadeAnim, 0.f, 1, EUMGSequencePlayMode::Forward);
}

void UTrainNotificationUI::SetMessage(const FText& Message)
{
	if (MessageText) MessageText->SetText(Message);
}

void UTrainNotificationUI::Disappear()
{
	if (FadeAnim)
	{
		bIsMarkedForDestoy = true; // Destroy UI after animation finished in blueprint
		PlayAnimation(FadeAnim, 0.f, 1, EUMGSequencePlayMode::Reverse);
	}
	else RemoveFromParent();
}