#include "ShopVisibleTrigger.h"

AShopVisibleTrigger::AShopVisibleTrigger()
{
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    SetRootComponent(TriggerBox);
    TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    TriggerBox->SetGenerateOverlapEvents(true);
}

void AShopVisibleTrigger::BeginPlay()
{
    Super::BeginPlay();
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AShopVisibleTrigger::OnBeginOverlap);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AShopVisibleTrigger::OnEndOverlap);
}

void AShopVisibleTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (ACustomer* Customer = Cast<ACustomer>(OtherActor))
    {
        if (!Shop) return;
        Customer->SeeShop(Shop);
    }
}

void AShopVisibleTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (ACustomer* Customer = Cast<ACustomer>(OtherActor)) {}
}

