#include "Customer.h"

ACustomer::ACustomer()
{
	PrimaryActorTick.bCanEverTick = true;
	NavigationMovementComponent = CreateDefaultSubobject<UNavigationMovementComponent>(TEXT("Navigation Movement"));
}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimerForNextTick(
		this, &ACustomer::GoToExit
	);
}

void ACustomer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomer::GoToExit()
{
	NavigationMovementComponent->MoveToPoint(ExitLocation);
}

