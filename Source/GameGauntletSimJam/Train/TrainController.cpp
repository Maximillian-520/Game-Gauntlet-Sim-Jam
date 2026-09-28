#include "TrainController.h"

ATrainController::ATrainController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATrainController::BeginPlay()
{
	Super::BeginPlay();

	// Delay of 1 seconds
	GetWorldTimerManager().SetTimer(
		DelayTimerHandle,
		this,
		&ATrainController::CreateIncomingTrain,
		1.0f,
		false
	);
	//CreateIncomingTrain();
}

void ATrainController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ==================================================
//           Controller
// ==================================================

void ATrainController::CreateIncomingTrain()
{
	CurrentTrain = TrainSpawner->SpawnTrain();
	CurrentTrain->OnDisembarkLocationReached.AddDynamic(this, &ATrainController::DisembrakTrain);
	CurrentTrain->OnDisappearLocationReached.AddDynamic(this, &ATrainController::DisappearTrain);

	CurrentTrain->GoToDisembarkLocation(DisembarkPoint->GetActorLocation());
}

void ATrainController::DisembrakTrain()
{
	CustomerSpawner->SpawnCustomerAtInterval(20, 0.25);

	// Delay of 3 seconds
	GetWorldTimerManager().SetTimer(
		DelayTimerHandle,
		this,
		&ATrainController::ToDisappearLocation,
		6.0f,
		false
	);
}

void ATrainController::ToDisappearLocation()
{
	CurrentTrain->GoToDisappearLocation(DisappearPoint->GetActorLocation());
}

void ATrainController::DisappearTrain()
{
	CurrentTrain->OnDisappearLocationReached.RemoveDynamic(this, &ATrainController::DisembrakTrain);
	CurrentTrain->OnDisappearLocationReached.RemoveDynamic(this, &ATrainController::DisembrakTrain);

	CurrentTrain->Destroy();
	CurrentTrain = nullptr;
}
