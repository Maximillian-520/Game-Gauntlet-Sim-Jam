#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common/MoneyManager.h"
#include "CustomerSpawner.h"
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
	void HandleCustomerSpawned(ACustomer* Customer);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandlePurchasedFromShop(int32 MoneySpent);

	UFUNCTION(BlueprintCallable, Category = "Controller")
	void HandleCustomerDestroyed(AActor* DestroyedActor);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:	
	TArray<ACustomer*> Customers;
};
