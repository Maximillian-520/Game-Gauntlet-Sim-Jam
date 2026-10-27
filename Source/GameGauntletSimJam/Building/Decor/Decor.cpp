#include "Decor.h"

ADecor::ADecor()
{
	//PrimaryActorTick.bCanEverTick = true;

}

void ADecor::BeginPlay()
{
	Super::BeginPlay();

	CustomerManager = UGameInstance::GetSubsystem<UCustomerManager>(GetGameInstance());
	if (!CustomerManager) UE_LOG(LogTemp, Warning, TEXT("CustomerManager did not exist"));
	
	UpdateBuildingEffect();
}

void ADecor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CustomerManager)
	{
		CustomerManager->AddSpawnIntervalReduction(-CurrentSpawnIntervalReduction);
		CustomerManager->AddInterestedChanceIncrease(-CurrentInterestedChanceIncrease);
	}

	Super::EndPlay(EndPlayReason);
}

//void ADecor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

void ADecor::Upgrade()
{
	Super::Upgrade();

	SetBuildingLevelMesh();

	UpdateBuildingEffect();
}

void ADecor::UpdateBuildingEffect()
{
	// --- Update Spawn Interval Reduction ---

	float NewSpawnIntervalReduction = CalculateSpawnIntervalReduction();
	float OffsetSpawnIntervalReduction = NewSpawnIntervalReduction - CurrentSpawnIntervalReduction;

	CurrentSpawnIntervalReduction = NewSpawnIntervalReduction;

	if (CustomerManager) CustomerManager->AddSpawnIntervalReduction(OffsetSpawnIntervalReduction);

	// --- Update Interested Chance Increase ---

	float NewInterestedChanceIncrease = CalculateInterestedChanceIncrease();
	float OffsetInterestedChanceIncrease = NewInterestedChanceIncrease - CurrentInterestedChanceIncrease;

	CurrentInterestedChanceIncrease = NewInterestedChanceIncrease;

	if (CustomerManager) CustomerManager->AddInterestedChanceIncrease(OffsetInterestedChanceIncrease);
}

float ADecor::CalculateSpawnIntervalReduction() const
{
	if (SpawnIntervalReductions.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, SpawnIntervalReductions.Num());

	return SpawnIntervalReductions[Index - 1];
}

float ADecor::CalculateInterestedChanceIncrease() const
{
	if (InterestedChanceIncreases.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, InterestedChanceIncreases.Num());

	return InterestedChanceIncreases[Index - 1];
}
