#include "Shop.h"

AShop::AShop()
{
	PrimaryActorTick.bCanEverTick = true;

	StandingArea = CreateDefaultSubobject<UBoxComponent>(TEXT("StandingArea"));
	if (Root) StandingArea->SetupAttachment(Root);
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
	return GetRandomPointInArea(StandingArea);
}

FRotator AShop::GetStandingDirection() const
{
	FRotator ReturnRotation = GetActorRotation();
	ReturnRotation.Yaw += 180.f;
	ReturnRotation.Normalize();
	return ReturnRotation;
}

int32 AShop::GetItemCost() const
{
	if (ItemCosts.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, ItemCosts.Num());
	
	return ItemCosts[Index - 1];
}

FVector AShop::GetRandomPointInArea(const UBoxComponent* Area) const
{
	if (!Area) return GetActorLocation();

	const FVector Extent = Area->GetUnscaledBoxExtent();

	// Random point in the local X/Y plane (Z = 0 keeps it flat)
	const FVector LocalPoint(
		FMath::FRandRange(-Extent.X, Extent.X),
		FMath::FRandRange(-Extent.Y, Extent.Y),
		0.f);

	// Converts to world space, respecting the component's location, rotation and scale
	return Area->GetComponentTransform().TransformPosition(LocalPoint);
}