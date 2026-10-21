#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuUI.h"
#include "MenuUIController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AMenuUIController : public AActor
{
	GENERATED_BODY()

public:
	AMenuUIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> UISpawnBlueprint;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UUserWidget* UI;
};