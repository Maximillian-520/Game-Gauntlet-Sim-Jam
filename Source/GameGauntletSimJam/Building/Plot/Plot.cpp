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

ABaseBuilding* APlot::BuildBuilding(TSubclassOf<ABaseBuilding> BuildingClass)
{
	if (!CanBuild(BuildingClass)) return nullptr;

	const int32 Cost = BuildingClass->GetDefaultObject<ABaseBuilding>()->BuildCost;

	UMoneyManager* Money = GetGameInstance()->GetSubsystem<UMoneyManager>();
	if (Money && !Money->TrySpend(Cost)) return nullptr;

	FActorSpawnParameters Params;
	Params.Owner = this;
	Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Building = GetWorld()->SpawnActor<ABaseBuilding>(
		BuildingClass, GetActorTransform(), Params
	);

	OnBuildingChanged.Broadcast(Building);
	return Building;
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

	if (!HasBuilding()) OnPlotClicked.Broadcast(this);
}

