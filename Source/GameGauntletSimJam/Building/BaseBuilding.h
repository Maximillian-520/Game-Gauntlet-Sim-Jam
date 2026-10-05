#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseBuilding.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ABaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	ABaseBuilding();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	int32 BuildCost = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building")
	int32 MaxLevel = 3;

	UFUNCTION(BlueprintPure, Category = "Building")
	int32 GetCurrentLevel() const { return Level; }

protected:

private:
	UPROPERTY(VisibleAnywhere, Category = "Building")
	int32 Level = 1;

};
