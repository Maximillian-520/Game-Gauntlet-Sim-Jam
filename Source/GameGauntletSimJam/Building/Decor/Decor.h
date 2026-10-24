#pragma once

#include "CoreMinimal.h"
// Custom
#include "../BaseBuilding.h"
#include "../../Common/Manager/CustomerManager.h"
// ==========
#include "Decor.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ADecor : public ABaseBuilding
{
	GENERATED_BODY()
	
public:	
	ADecor();
	
	virtual void Upgrade();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Decor")
	TArray<float> SpawnIntervalReductions = TArray<float>{ 0.1 };

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//virtual void Tick(float DeltaTime) override;

	void UpdateSpawnIntervalReduction();

	float CalculateSpawnIntervalReduction() const;

private:
	float CurrentSpawnIntervalReduction;
};
