#include "Plot.h"

APlot::APlot()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	BuildingRoot = CreateDefaultSubobject<USceneComponent>(TEXT("BuildingRoot"));
	BuildingRoot->SetupAttachment(Root);

	ClickArea = CreateDefaultSubobject<UBoxComponent>(TEXT("ClickArea"));
	ClickArea->SetupAttachment(Root);
	ClickArea->SetCollisionProfileName(TEXT("BlockAllDynamic"));
	ClickArea->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void APlot::NotifyActorOnClicked(FKey ButtonPressed)
{
	Super::NotifyActorOnClicked(ButtonPressed);

	OnPlotClicked.Broadcast(this);
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
		BuildingBlueprint, BuildingRoot->GetComponentTransform(), Params
	);

	if (Building)
	{
		Building->AttachToComponent(
			BuildingRoot,
			FAttachmentTransformRules::SnapToTargetNotIncludingScale
		);
	}

	SetPlot();

	OnBuildingChanged.Broadcast(Building);
	return Building;
}

void APlot::UpgradeBuilding()
{
	if (Building)
	{
		Building->Upgrade();

		OnBuildingChanged.Broadcast(Building);
	}

	SetPlot();
}

void APlot::DemolishBuilding()
{
	if (Building)
	{
		DestoryedBuilding = Building;
		Building = nullptr;
		OnBuildingChanged.Broadcast(nullptr);
		OnBuildingDestoryed.Broadcast();
	}

	SetPlot();
}

void APlot::DestroyBuilding()
{
	if (DestoryedBuilding)
	{
		DestoryedBuilding->Destroy();
		DestoryedBuilding = nullptr;

		BuildingRoot->SetRelativeScale3D(FVector::OneVector);
	}
}

void APlot::SetPlot()
{
	SetActorHiddenInGame(Building != nullptr);
}
