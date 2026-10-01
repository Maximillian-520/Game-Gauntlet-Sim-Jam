#include "GameUIController.h"
#include "Kismet/GameplayStatics.h"

AGameUIController::AGameUIController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameUIController::BeginPlay()
{
	Super::BeginPlay();

    if (MoneyUIBlueprint)
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
        if (PC)
        {
            MoneyUIWidget = CreateWidget<UMoneyUI>(PC, MoneyUIBlueprint);
            if (MoneyUIWidget) MoneyUIWidget->AddToViewport();
        }
    }
}

void AGameUIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (MoneyUIWidget)
    {
        MoneyUIWidget->RemoveFromParent();
        MoneyUIWidget = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

