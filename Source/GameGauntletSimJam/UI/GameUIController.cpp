#include "GameUIController.h"
#include "Kismet/GameplayStatics.h"

AGameUIController::AGameUIController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameUIController::BeginPlay()
{
	Super::BeginPlay();

    // --- Spawn all UI ---
    APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
    if (!PC) return;

    for (TSubclassOf<UUserWidget> UIBlueprint : UISpawnBlueprints)
    {
        UUserWidget* UI = CreateWidget<UUserWidget>(PC, UIBlueprint);
        if (UI)
        {
            UI->AddToViewport();
            UIs.Add(UI);
        }
    }
}

void AGameUIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (UUserWidget* UI : UIs) UI->RemoveFromParent();
    UIs.Empty();

    Super::EndPlay(EndPlayReason);
}

