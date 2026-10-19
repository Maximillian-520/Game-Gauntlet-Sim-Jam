#include "Train.h"

TSet<int32> ATrain::UsedInstanceNumber;

ATrain::ATrain()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);

	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("HitBox"));
	HitBox->SetupAttachment(DefaultSceneRoot);
	HitBox->SetBoxExtent(FVector(200.f, 100.f, 100.f));
	HitBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	HitBox->SetGenerateOverlapEvents(true);

	LinearMovementComponent = CreateDefaultSubobject<ULinearMovementComponent>(TEXT("LinearMovementComponent"));
}

void ATrain::BeginPlay()
{
	Super::BeginPlay();

	HitBox->OnComponentBeginOverlap.AddDynamic(this, &ATrain::OnHitBoxBeginOverlap);

	TrainNumber = GenerateUniqueNumber();

	Travel();
}

void ATrain::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (TrainNumber != 0) ClearUniqueNumber(TrainNumber);

	Super::EndPlay(EndPlayReason);
}

void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// --- Traveling ---
	if (bIsTraveling)
	{
		TravelTimer -= DeltaTime;
		if (TravelTimer <= 0)
		{
			OnTrainArrived.Broadcast(this);
			OnTrainArrivedBP();
		}

		TravelUpdateTimer -= DeltaTime;
		if (TravelUpdateTimer <= 0)
		{
			OnTrainTravelUpdate.Broadcast(this);
			TravelUpdateTimer = TravelUpdateInterval;
		}
	}

	// --- Passing ---
	if (LinearMovementComponent && bIsPassing)
	{
		const FVector ToTarget = PassTargetLocation - GetActorLocation();
		const float DistanceToTarget = ToTarget.Size();

		LinearMovementComponent->SetDirection(ToTarget);
		LinearMovementComponent->Forward();

		// Close enough to reach the target this frame (also prevents overshooting)
		if (DistanceToTarget <= AcceptanceRadius)
		{
			HandlePointReached();
			return;
		}
	}

}

// ==================================================
//           Main
// ==================================================

void ATrain::Travel()
{
	bIsTraveling = true;
	bIsPassing = false;
	TravelTimer = FMath::FRandRange(MinTravelDuration, MaxTravelDuration);
	TravelUpdateTimer = TravelUpdateInterval;
	SetActorHiddenInGame(true);
}

void ATrain::PassThrough()
{
	bIsTraveling = false;
	bIsPassing = true;
	SetActorHiddenInGame(false);
	LinearMovementComponent->SetVelocity(LinearMovementComponent->MoveSpeed);
}

void ATrain::HandlePointReached()
{
	// Destroy after reaching target location
	Destroy();
}

void ATrain::OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACustomer* Customer = Cast<ACustomer>(OtherActor);
	if (!Customer) return;

	OnTrainHitCustomer.Broadcast(Customer);
	OnTrainHitCustomerBP();
}

// ==================================================
//           Naming
// ==================================================

FText ATrain::GetTrainName() const
{
	FNumberFormattingOptions Options;
	Options.UseGrouping = false;
	Options.MinimumIntegralDigits = 3;

	FText TrainNumberText = FText::AsNumber(TrainNumber, &Options);

	return FText::Format(INVTEXT("{0}-{1}"), TrainCode, TrainNumberText);
}

int32 ATrain::GenerateUniqueNumber() const
{
	int32 Number = 0;

	// Keep randomizing number if random number already exist,
	// capped to MaxRandomIteration interations
	for (int32 Index = 0; Index < MaxRandomIteration; Index++)
	{
		int32 RandomNumber = FMath::RandRange(1, 999);
		if (!UsedInstanceNumber.Contains(RandomNumber))
		{
			Number = RandomNumber;
			break;
		}
	}

	if (Number != 0) UsedInstanceNumber.Add(Number);

	return Number;
}

void ATrain::ClearUniqueNumber(int32 Number) const
{
	if (UsedInstanceNumber.Contains(Number)) UsedInstanceNumber.Remove(Number);
}