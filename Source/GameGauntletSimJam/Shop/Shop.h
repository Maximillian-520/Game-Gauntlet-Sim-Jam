#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "Shop.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AShop : public AActor
{
	GENERATED_BODY()
	
public:	
	AShop();

	UFUNCTION(BlueprintCallable, Category = "Shop")
	FVector GetStandingLocation();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shop")
	TObjectPtr<USceneComponent> StandingMarker;

private:
	

};
