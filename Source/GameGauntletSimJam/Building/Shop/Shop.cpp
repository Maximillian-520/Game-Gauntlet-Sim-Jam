#include "Shop.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = true;

	StandingMarker = CreateDefaultSubobject<USceneComponent>(TEXT("StandingMarker"));
	if (Root) StandingMarker->SetupAttachment(Root);
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

	SetBuildingLevelMesh();
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