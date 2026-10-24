#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
// Custom
#include "CustomerSpawner.h"
#include "../Common/Manager/CustomerManager.h"
#include "../Common/Manager/MoneyManager.h"
// ==========
#include "CustomerController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomerController : public AActor
{
	GENERATED_BODY()
	
public:	
	ACustomerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Controller")
	ACustomerSpawner* CustomerSpawner;

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void StartMakingWay();

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void EndMakingWay();

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void UpdateSpawnInterval();

	UFUNCTION(BlueprintImplementableEvent, Category = "Controller")
	void OnStartMakingWayBP();

	UFUNCTION(BlueprintImplementableEvent, Category = "Controller")
	void OnEndMakingWayBP();

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleCustomerSpawned(ACustomer* Customer);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandlePurchasedFromShop(int32 MoneySpent);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleCustomerDestroyed(AActor* DestroyedActor);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleSpawnIntervalChanged() { UpdateSpawnInterval(); }

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	UCustomerManager* CustomerManager = nullptr;
	UPROPERTY()
	UMoneyManager* MoneyManager = nullptr;

	TArray<ACustomer*> Customers;
};
