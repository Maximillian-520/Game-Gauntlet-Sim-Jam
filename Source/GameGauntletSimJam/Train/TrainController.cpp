#include "TrainController.h"

ATrainController::ATrainController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATrainController::BeginPlay()
{
	Super::BeginPlay();
	
	GameManager = UGameInstance::GetSubsystem<UGameManager>(GetGameInstance());
	if (!GameManager) UE_LOG(LogTemp, Warning, TEXT("GameManager did not exist"));
	TrainManager = UGameInstance::GetSubsystem<UTrainManager>(GetGameInstance());
	if (!TrainManager) UE_LOG(LogTemp, Warning, TEXT("TrainManager did not exist"));

	if (TrainManager)
		TrainManager->OnTrackIntervalChanged.AddDynamic(this, &ATrainController::HandleTrackIntervalChanged);
	TrainSpawner->OnTrainSpawned.AddDynamic(this, &ATrainController::HandleTrainSpawned);
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
	if (!TrainManager) return;

	for (ATrain* Train : Trains)
	{
		Train->TravelUpdateInterval = TrainManager->GetCalculatedTrackInterval(TrainCount);
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
	// --- Setup train and update ---

	Train->OnTrainTravelUpdate.AddDynamic(this, &ATrainController::HandleTrainTravelUpdate);
	Train->OnTrainArrived.AddDynamic(this, &ATrainController::HandleTrainArrived);
	Train->OnTrainHitCustomer.AddDynamic(this, &ATrainController::HandleTrainHitCustomer);
	Train->OnDestroyed.AddDynamic(this, &ATrainController::HandleTrainDestroyed);

	Trains.Add(Train);
	TrainCount++;
	UpdateTrainTrackInterval();
	
	if (TrainManager) Train->TravelUpdateInterval = TrainManager->GetCalculatedTrackInterval(TrainCount);

	if (TrainCount >= MaxTrainCount) TrainSpawner->StopSpawning();

	// --- Notify that train has spawned ---

	if (TrainManager) if (TrainManager->CanTrackTrains())
	{
		FText TrainName = Train->GetTrainName();
		BroadcastOnNotificationRequested(
			Train->TrainType, TrainName, GetFormatedDistanceText(Train->GetTrainRemainingDistance())
		);
	}
}

void ATrainController::HandleTrainTravelUpdate(ATrain* Train)
{
	if (TrainManager) if (TrainManager->CanTrackTrains())
	{
		FText TrainName = Train->GetTrainName();
		BroadcastOnNotificationRequested(
			Train->TrainType, TrainName, GetFormatedDistanceText(Train->GetTrainRemainingDistance())
		);
	}
}

void ATrainController::HandleTrainArrived(ATrain* Train)
{
	if (TrainManager) if (TrainManager->CanTrackTrains())
	{
		FText TrainName = Train->GetTrainName();
		BroadcastOnNotificationRequested(Train->TrainType, TrainName, FText::FromString("Arrived"));
	}

	TrainPassQueue.Add(Train);
	CheckTrainPassQueue();
}

void ATrainController::HandleTrainHitCustomer(ACustomer* HitCustomer)
{
	if (GameManager) GameManager->LoseGame();
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
