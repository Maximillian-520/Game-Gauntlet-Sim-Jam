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

protected:

private:

};
