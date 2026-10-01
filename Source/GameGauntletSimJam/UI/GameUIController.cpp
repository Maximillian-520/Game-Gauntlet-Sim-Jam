#include "GameUIController.h"
#include "Kismet/GameplayStatics.h"

AGameUIController::AGameUIController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameUIController::BeginPlay()
{
	Super::BeginPlay();

    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);

    if (MoneyUIBlueprint)
    {
        if (PC)
        {
            MoneyUI = CreateWidget<UMoneyUI>(PC, MoneyUIBlueprint);
            if (MoneyUI) MoneyUI->AddToViewport();
        }
    }

    if (CustomerControlUIBlueprint)
    {
        if (PC)
        {
            CustomerControlUI = CreateWidget<UCustomerControlUI>(PC, CustomerControlUIBlueprint);
            if (CustomerControlUI) CustomerControlUI->AddToViewport();
        }
    }
}

void AGameUIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (MoneyUI)
    {
        MoneyUI->RemoveFromParent();
        MoneyUI = nullptr;
    }
    if (CustomerControlUI)
    {
        CustomerControlUI->RemoveFromParent();
        CustomerControlUI = nullptr;
    }
    Super::EndPlay(EndPlayReason);
}

