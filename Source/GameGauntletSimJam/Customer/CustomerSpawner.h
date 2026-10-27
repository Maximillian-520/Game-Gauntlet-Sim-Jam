#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "Components/BoxComponent.h"
// Custom
#include "Customer.h"
// ==========
#include "CustomerSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomerSpawned, ACustomer*, Customer);

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerSpawner();

	// ==================================================
	//           Reference
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Reference")
	AActor* CustomerInstanceParent;

	// ==================================================
	//           Main
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Main")
	TSubclassOf<ACustomer> CustomerBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawner|Main")
	TArray<ATriggerBox*> SpawnAreas;

	UFUNCTION(BlueprintCallable, Category = "Spawner|Main")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner|Main")
	void StopSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner|Main")
	void SpawnCustomer();

	UBoxComponent* GetNearestSpawnArea(const FVector CurrentLocation);

	FVector GetRandomPointInArea(const UBoxComponent* Area) const;
	
	UPROPERTY(BlueprintAssignable, Category = "Spawner|Main")
	FOnCustomerSpawned OnCustomerSpawned;
	
	// ==================================================
	//           Settings
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	bool bStartSpawningImmediately = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner|Settings")
	bool bIsSpawning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float MinSpawnInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float MaxSpawnInterval = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float InterestedChanceIncreaseModifier = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner|Settings")
	float PurchaseChanceIncreaseModifier = 0.0f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	float SpawnTimer;

	void ResetSpawnTimer();

};
