#include "Shop.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	StandingMarker = CreateDefaultSubobject<USceneComponent>(TEXT("StandingMarker"));
	StandingMarker->SetupAttachment(Root);
}

void AShop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AShop::GetStandingLocation()
{
	return StandingMarker ? StandingMarker->GetComponentLocation() : GetActorLocation();
}
