#pragma once

#include "CoreMinimal.h"
#include "../BaseBuilding.h"
#include "Engine/TargetPoint.h"
#include "Shop.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AShop : public ABaseBuilding
{
	GENERATED_BODY()
	
public:	
	AShop();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	FVector GetStandingLocation();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	int32 ItemCost = 1;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<USceneComponent> StandingMarker;

private:
	

};
