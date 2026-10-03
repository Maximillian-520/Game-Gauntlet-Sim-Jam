#include "TrainControlUI.h"

void UTrainControlUI::NativeConstruct()
{
	Super::NativeConstruct();

	ViewModel = NewObject<UTrainViewModel>(this);

	if (ATrainController* Controller = Cast<ATrainController>(
		UGameplayStatics::GetActorOfClass(this, ATrainController::StaticClass())))
	{
		ViewModel->Initialize(Controller);
	}

	ViewModel->OnNotificationRequested.AddDynamic(this, &UTrainControlUI::HandleNotificationRequested);
}

void UTrainControlUI::NativeDestruct()
{
	if (ViewModel) ViewModel->OnNotificationRequested.RemoveDynamic(this, &UTrainControlUI::HandleNotificationRequested);

	Super::NativeDestruct();
}

UTrainNotificationUI* UTrainControlUI::SpawnNotification(const FText& Message)
{

	if (!TrainNotificationUIBlueprint || !NotificationBox) return nullptr;

	UTrainNotificationUI* Notification = CreateWidget<UTrainNotificationUI>(GetOwningPlayer(), TrainNotificationUIBlueprint);
	if (!Notification) return nullptr;

	// Set the message BEFORE adding it, so it's ready when NativeConstruct runs
	Notification->NotificationMessage = Message;

	NotificationBox->AddChild(Notification);

	return Notification;
}

void UTrainControlUI::HandleNotificationRequested(const FText& Message)
{
	SpawnNotification(Message);
}

void UTrainControlUI::RemoveNotification(UTrainNotificationUI* Notification)
{
	if (Notification) Notification->RemoveFromParent();
}