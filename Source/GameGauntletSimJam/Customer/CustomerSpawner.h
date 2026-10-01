#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerBox.h"
#include "Components/BoxComponent.h"
#include "Customer.h"
#include "CustomerSpawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCustomerSpawned, ACustomer*, Customer);

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomerSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerSpawner();

	// ==================================================
	//           Spawner
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<ACustomer> CustomerBlueprint;

	UPROPERTY(EditAnywhere, Category = "Spawner")
	TArray<ATriggerBox*> SpawnAreas;

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StartSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void StopSpawning();

	UFUNCTION(BlueprintCallable, Category = "Spawner")
	void SpawnCustomer();

	UBoxComponent* GetNearestSpawnArea(const FVector CurrentLocation);

	FVector GetRandomPointInArea(const UBoxComponent* Area) const;
	
	UPROPERTY(BlueprintAssignable, Category = "Spawner")
	FOnCustomerSpawned OnCustomerSpawned;
	
	// ==================================================
	//           Settings
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	bool bStartSpawningImmediately = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings")
	bool bIsSpawning = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MinSpawnInterval = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Settings")
	float MaxSpawnInterval = 2.0f;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	float SpawnTimer;

	void ResetSpawnTimer();

};
