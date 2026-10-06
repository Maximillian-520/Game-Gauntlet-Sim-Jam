#include "TrainController.h"
#include "Kismet/GameplayStatics.h" // Temp

ATrainController::ATrainController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATrainController::BeginPlay()
{
	Super::BeginPlay();
	
	TrainSpawner->OnTrainSpawned.AddDynamic(this, &ATrainController::HandleTrainSpawned);
	if (UTrackerManager* TrackerManager = UGameInstance::GetSubsystem<UTrackerManager>(GetGameInstance()))
	{
		TrackerManager->OnTrackIntervalChanged.AddDynamic(this, &ATrainController::HandleTrackIntervalChanged);
	}
}

void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ==================================================
//           Controller
// ==================================================

void ATrainController::UpdateTrainTrackInterval()
{
	UTrackerManager* TrackerManager = UGameInstance::GetSubsystem<UTrackerManager>(GetGameInstance());
	if (!TrackerManager) return;

	for (ATrain* Train : Trains)
	{
		Train->TravelUpdateInterval = TrackerManager->GetCalculatedTrackInterval(TrainCount);
	}
}

FText ATrainController::GetFormatedDistanceText(float Distance)
{
	// Distance is in kilometers
	if (Distance < 1.0f)
	{
		const int32 Meters = FMath::RoundToInt(Distance * 1000.0f);
		return FText::Format(NSLOCTEXT("Train", "DistanceMeters", "{0} m"), FText::AsNumber(Meters));
	}

	FNumberFormattingOptions Options;
	Options.MinimumFractionalDigits = 0;
	Options.MaximumFractionalDigits = 1;

	return FText::Format(NSLOCTEXT("Train", "DistanceKilometers", "{0} km"), FText::AsNumber(Distance, &Options));
}

void ATrainController::CheckTrainPassQueue()
{
	if (CurrentTrainPassing) return;
	if (TrainPassQueue.Num() <= 0) return;

	CurrentTrainPassing = TrainPassQueue[0];
	TrainPassQueue.RemoveAt(0);

	CurrentTrainPassing->AllowPassThrough();
}

// ==================================================
//           Event
// ==================================================

void ATrainController::HandleTrainSpawned(ATrain* Train)
{
	Train->OnTrainTravelUpdate.AddDynamic(this, &ATrainController::HandleTrainTravelUpdate);
	Train->OnTrainArrived.AddDynamic(this, &ATrainController::HandleTrainArrived);
	Train->OnTrainHitCustomer.AddDynamic(this, &ATrainController::HandleTrainHitCustomer);
	Train->OnDestroyed.AddDynamic(this, &ATrainController::HandleTrainDestroyed);
	
	if (UTrackerManager* TrackerManager = UGameInstance::GetSubsystem<UTrackerManager>(GetGameInstance()))
	{
		Train->TravelUpdateInterval = TrackerManager->GetCalculatedTrackInterval(TrainCount);
	}

	Trains.Add(Train);
	TrainCount++;
	UpdateTrainTrackInterval();

	if (TrainCount >= MaxTrainCount) TrainSpawner->StopSpawning();

	FText TrainName = Train->GetTrainName();
	FText TrainText = FText::Format(
		INVTEXT("{0} {1} was spotted from {2}"),
		Train->TrainType,
		TrainName,
		GetFormatedDistanceText(Train->GetTrainRemainingDistance())
	);
	BroadcastOnNotificationRequested(TrainName, TrainText);
}

void ATrainController::HandleTrainTravelUpdate(ATrain* Train)
{
	FText TrainName = Train->GetTrainName();
	FText TrainText = FText::Format(
		INVTEXT("{0} {1} is closing in at {2}"),
		Train->TrainType,
		TrainName,
		GetFormatedDistanceText(Train->GetTrainRemainingDistance())
	);
	BroadcastOnNotificationRequested(TrainName, TrainText);
}

void ATrainController::HandleTrainArrived(ATrain* Train)
{
	FText TrainName = Train->GetTrainName();
	FText TrainText = FText::Format(
		INVTEXT("{0} {1} has arrived"),
		Train->TrainType,
		TrainName
	);
	BroadcastOnNotificationRequested(TrainName, TrainText);

	TrainPassQueue.Add(Train);
	CheckTrainPassQueue();
}

void ATrainController::HandleTrainHitCustomer(ACustomer* HitCustomer)
{
	// Temp
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ATrainController::HandleTrainDestroyed(AActor* DestroyedActor)
{
	ATrain* Train = Cast<ATrain>(DestroyedActor);

	FText TrainName = Train->GetTrainName();
	BroadcastOnNotificationDeleted(TrainName);

	Trains.Remove(Train);
	TrainCount--;

	CurrentTrainPassing = nullptr;
	CheckTrainPassQueue();

	if (TrainCount < MaxTrainCount) TrainSpawner->StartSpawning();
}
