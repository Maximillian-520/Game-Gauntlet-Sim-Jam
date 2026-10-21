#include "MenuUIController.h"

AMenuUIController::AMenuUIController()
{
    PrimaryActorTick.bCanEverTick = true;

}

void AMenuUIController::BeginPlay()
{
    Super::BeginPlay();

    // --- Spawn UI ---
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC) return;

    UI = CreateWidget<UUserWidget>(PC, UISpawnBlueprint);
    if (UI) UI->AddToViewport();
}

void AMenuUIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UI->RemoveFromParent();
    UI = nullptr;

    Super::EndPlay(EndPlayReason);
}