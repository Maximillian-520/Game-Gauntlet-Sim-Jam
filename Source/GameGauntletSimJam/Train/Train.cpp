#include "Train.h"

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

	Travel();
}

void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// --- Traveling ---
	if (bIsTraveling)
	{
		TravelTimer -= DeltaTime;
		if (TravelTimer <= 0) PassThrough();
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

void ATrain::Travel()
{
	bIsTraveling = true;
	bIsPassing = false;
	TravelTimer = FMath::FRandRange(MinTravelDuration, MaxTravelDuration);
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
}
