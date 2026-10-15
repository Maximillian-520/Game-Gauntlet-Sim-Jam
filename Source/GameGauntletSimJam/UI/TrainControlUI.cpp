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
	ViewModel->OnNotificationDeleted.AddDynamic(this, &UTrainControlUI::HandleNotificationDeleted);
}

void UTrainControlUI::NativeDestruct()
{
	if (ViewModel) ViewModel->OnNotificationRequested.RemoveDynamic(this, &UTrainControlUI::HandleNotificationRequested);

	Super::NativeDestruct();
}

UTrainNotificationUI* UTrainControlUI::SpawnOrUpdateNotification(const FText& TrainType, const FText& TrainName, const FText& Status)
{
	UTrainNotificationUI* Notification = nullptr;
	FName Key(*TrainName.ToString());

	// Find existing one
	if (TrainNotificationMap.Contains(Key)) Notification = TrainNotificationMap.FindRef(Key);


	// Update if found
	if (Notification) Notification->Update(Status);
	// Create if not found
	else if (TrainNotificationUIBlueprint || NotificationBox)
	{
		Notification = CreateWidget<UTrainNotificationUI>(GetOwningPlayer(), TrainNotificationUIBlueprint);
		if (!Notification) return nullptr;
		NotificationBox->AddChild(Notification);
		TrainNotificationMap.Add(Key, Notification);
		Notification->Show(TrainType, TrainName, Status);
	}

	return Notification;
}

void UTrainControlUI::RemoveNotification(const FText& TrainName)
{
	UTrainNotificationUI* Notification = nullptr;
	FName Key(*TrainName.ToString());

	if (TrainNotificationMap.Contains(Key))
	{
		Notification = TrainNotificationMap.FindRef(Key);
		if (Notification) Notification->Disappear();
		TrainNotificationMap.Remove(Key);
	}
}

void UTrainControlUI::RemoveNotification(UTrainNotificationUI* Notification)
{
	if (!Notification) return;

	Notification->Disappear();

	if (const FName* Key = TrainNotificationMap.FindKey(Notification))
	{
		const FName KeyCopy = *Key; // copy first: Key points into the map
		TrainNotificationMap.Remove(KeyCopy);
	}
}

void UTrainControlUI::HandleNotificationRequested(const FText& TrainType, const FText& TrainName, const FText& Message)
{
	SpawnOrUpdateNotification(TrainType, TrainName, Message);
}

void UTrainControlUI::HandleNotificationDeleted(const FText& TrainName)
{
	RemoveNotification(TrainName);
}