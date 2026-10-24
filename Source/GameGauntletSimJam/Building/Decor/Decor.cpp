#include "Decor.h"

ADecor::ADecor()
{
	//PrimaryActorTick.bCanEverTick = true;

}

void ADecor::BeginPlay()
{
	Super::BeginPlay();
	
	UpdateSpawnIntervalReduction();
}

void ADecor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UCustomerManager* CustomerManager = UGameInstance::GetSubsystem<UCustomerManager>(GetGameInstance()))
	{
		CustomerManager->AddSpawnIntervalReduction(-CalculateSpawnIntervalReduction());
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

	UpdateSpawnIntervalReduction();
}

void ADecor::UpdateSpawnIntervalReduction()
{
	float NewSpawnIntervalReduction = CalculateSpawnIntervalReduction();
	float OffsetSpawnIntervalReduction = NewSpawnIntervalReduction - CurrentSpawnIntervalReduction;

	CurrentSpawnIntervalReduction = NewSpawnIntervalReduction;

	if (UCustomerManager* CustomerManager = UGameInstance::GetSubsystem<UCustomerManager>(GetGameInstance()))
	{
		CustomerManager->AddSpawnIntervalReduction(OffsetSpawnIntervalReduction);
	}
}

float ADecor::CalculateSpawnIntervalReduction() const
{
	if (SpawnIntervalReductions.Num() <= 0) return 0;

	int32 Index = FMath::Min(Level, SpawnIntervalReductions.Num());

	return SpawnIntervalReductions[Index - 1];
}
