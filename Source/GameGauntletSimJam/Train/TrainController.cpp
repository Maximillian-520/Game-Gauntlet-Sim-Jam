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
}

void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATrainController::HandleTrainSpawned(ATrain* Train)
{
	Train->OnTrainHitCustomer.AddDynamic(this, &ATrainController::HandleTrainHitCustomer);
	Train->OnDestroyed.AddDynamic(this, &ATrainController::HandleTrainDestroyed);
	Trains.Add(Train);

	BroadcastOnNotification(FText::FromString(TEXT("Train is comming")));
}

void ATrainController::HandleTrainHitCustomer(ACustomer* HitCustomer)
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void ATrainController::HandleTrainDestroyed(AActor* DestroyedActor)
{
	Trains.Remove(Cast<ATrain>(DestroyedActor));
}
