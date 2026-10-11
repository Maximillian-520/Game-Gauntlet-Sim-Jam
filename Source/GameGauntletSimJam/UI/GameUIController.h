#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoneyUI.h"
#include "LoseUI.h"
#include "CustomerControlUI.h"
#include "TrainControlUI.h"
#include "BuildingControlUI.h"
#include "GameUIController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AGameUIController : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameUIController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TArray<TSubclassOf<UUserWidget>> UISpawnBlueprints;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	TArray<UUserWidget*> UIs;

};
