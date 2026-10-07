#include "Plot.h"

APlot::APlot()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	ClickArea = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickArea"));
	ClickArea->SetupAttachment(Root);
	ClickArea->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ClickArea->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

bool APlot::CanBuild(TSubclassOf<ABaseBuilding> BuildingClass) const
{
	return BuildingClass && !HasBuilding();
}

ABaseBuilding* APlot::BuildBuilding(TSubclassOf<ABaseBuilding> BuildingBlueprint)
{
	if (!CanBuild(BuildingBlueprint)) return nullptr;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Building = GetWorld()->SpawnActor<ABaseBuilding>(
		BuildingBlueprint, GetActorTransform(), Params
	);

	OnBuildingChanged.Broadcast(Building);
	return Building;
}

void APlot::UpgradeBuilding()
{
	if (Building)
	{
		Building->Upgrade();

		OnBuildingChanged.Broadcast(nullptr);
	}
}

void APlot::DemolishBuilding()
{
	if (Building)
	{
		Building->Destroy();
		Building = nullptr;
		OnBuildingChanged.Broadcast(nullptr);
	}
}

void APlot::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	OnPlotClicked.Broadcast(this);
}

