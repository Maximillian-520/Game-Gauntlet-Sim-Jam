#include "BaseBuilding.h"

ABaseBuilding::ABaseBuilding()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
}

void ABaseBuilding::BeginPlay()
{
	Super::BeginPlay();

	SetBuildingLevelMesh();
}

void ABaseBuilding::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (CurrentBuildingLevelMesh)
	{
		CurrentBuildingLevelMesh->Destroy();
		CurrentBuildingLevelMesh = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

// ==================================================
//           Main
// ==================================================

void ABaseBuilding::SetBuildingLevelMesh()
{
	// Remove the previous level's actor
	if (CurrentBuildingLevelMesh)
	{
		CurrentBuildingLevelMesh->Destroy();
		CurrentBuildingLevelMesh = nullptr;
	}

	if (BuildingLevelBlueprints.IsEmpty()) return;

	// Level is 1-based; fall back to the last entry if there are fewer blueprints than levels
	const int32 BlueprintIndex = FMath::Clamp(Level - 1, 0, BuildingLevelBlueprints.Num() - 1);

	const TSubclassOf<AActor> LevelClass = BuildingLevelBlueprints[BlueprintIndex];
	if (!LevelClass) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	CurrentBuildingLevelMesh = World->SpawnActor<AActor>(LevelClass, GetActorTransform(), SpawnParams);

	if (CurrentBuildingLevelMesh)
	{
		CurrentBuildingLevelMesh->AttachToComponent(Root, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	}
}

// ==================================================
//           Upgrade
// ==================================================

void ABaseBuilding::Upgrade()
{
	Level = FMath::Clamp(Level + 1, 1, MaxLevel);
}

// ==================================================
//           Demolish
// ==================================================

int32 ABaseBuilding::GetDemolishValue() const
{
	int32 Value = BuildCost;
	
	for (int Index = 0; Index < Level - 1; Index++)
	{
		if (Index >= UpgradeCosts.Num()) break;
		Value += UpgradeCosts[Index];
	}

	return Value * DemolishValueMargin;
}