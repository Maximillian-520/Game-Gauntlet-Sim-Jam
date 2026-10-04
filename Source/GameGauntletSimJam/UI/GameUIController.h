#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoneyUI.h"
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

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMoneyUI> MoneyUIBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCustomerControlUI> CustomerControlUIBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTrainControlUI> TrainControlUIBlueprint;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UBuildingControlUI> BuildingControlUIBlueprint;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UMoneyUI* MoneyUI;
	UCustomerControlUI* CustomerControlUI;
	UTrainControlUI* TrainControlUI;
	UBuildingControlUI* BuildingControlUI;

};
