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

    if (TrainControlUIBlueprint)
    {
        if (PC)
        {
            TrainControlUI = CreateWidget<UTrainControlUI>(PC, TrainControlUIBlueprint);
            if (TrainControlUI) TrainControlUI->AddToViewport();
        }
    }

    if (BuildingControlUIBlueprint)
    {
        if (PC)
        {
            BuildingControlUI = CreateWidget<UBuildingControlUI>(PC, BuildingControlUIBlueprint);
            if (BuildingControlUI) BuildingControlUI->AddToViewport();
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
    if (TrainControlUI)
    {
        TrainControlUI->RemoveFromParent();
        TrainControlUI = nullptr;
    }
    if (BuildingControlUI)
    {
        BuildingControlUI->RemoveFromParent();
        BuildingControlUI = nullptr;
    }

    Super::EndPlay(EndPlayReason);
}

