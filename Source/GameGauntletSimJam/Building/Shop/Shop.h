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

	virtual void Upgrade();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	FVector GetStandingLocation() const;

	UFUNCTION(BlueprintCallable, Category = "Shop")
	int32 GetItemCost() const;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<USceneComponent> StandingMarker;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shop")
	TArray<int32> ItemCosts = TArray<int32>{10};

private:
};
