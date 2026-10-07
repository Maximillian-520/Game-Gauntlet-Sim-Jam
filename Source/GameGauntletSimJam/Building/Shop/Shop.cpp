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

void AShop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShop::Upgrade()
{
	Super::Upgrade();
}

FVector AShop::GetStandingLocation() const
{
	return StandingMarker ? StandingMarker->GetComponentLocation() : GetActorLocation();
}

int32 AShop::GetItemCost() const
{
	if (ItemCosts.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, ItemCosts.Num());
	
	return ItemCosts[Index - 1];
}
