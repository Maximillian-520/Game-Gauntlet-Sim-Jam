#include "BuildingVisibleTrigger.h"

ABuildingVisibleTrigger::ABuildingVisibleTrigger()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    TriggerBox->SetGenerateOverlapEvents(true);
}

void ABuildingVisibleTrigger::BeginPlay()
{
    Super::BeginPlay();
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ABuildingVisibleTrigger::OnBeginOverlap);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ABuildingVisibleTrigger::OnEndOverlap);
}

void ABuildingVisibleTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACustomer* Customer = Cast<ACustomer>(OtherActor))
    {
        if (Plots.Num() <= 0) return;

        for (APlot* Plot : Plots)
        {
            ABaseBuilding* Building = Plot->Building;
            if (!Building) return;

            Customer->SeeBuilding(Building);
        }
    }
}

void ABuildingVisibleTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (ACustomer* Customer = Cast<ACustomer>(OtherActor)) {}
}
