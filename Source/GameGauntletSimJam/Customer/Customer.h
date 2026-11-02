#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Common/Component/CrowdMovementComponent.h"
#include "CustomerBehaviorComponent.h"
#include "Customer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCustomerDestroy);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPurchasedFromShop, int32, MoneySpent);

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomer : public AActor
{
	GENERATED_BODY()

public:
	ACustomer();

	// ==================================================
	//           Component
	// ==================================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Customer|Component")
	UCrowdMovementComponent* CrowdMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Customer|Component")
	UCustomerBehaviorComponent* CustomerBehaviorComponent;

	// ==================================================
	//           Customer
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customer",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float InterestedChance = 0.3f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Customer",
		meta = (ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	float PurchaseChance = 0.5f;

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void StrollAround();

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void SeeBuilding(ABaseBuilding* Building);

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void MakeWay(AActor* MakeWayActor, const FVector& MakeWayLocation, const FRotator& MakeWayRotation);
	
	UFUNCTION(BlueprintCallable, Category = "Customer")
	void SetExit(AActor* ExitActor, const FVector& ExitLocation, const FRotator& ExitRotation);

	UFUNCTION(BlueprintCallable, Category = "Customer")
	bool IsActive() { return bIsActive; }

	// ==================================================
	//           Event
	// ==================================================
	UFUNCTION()
	void HandleCustomerExited();

	UFUNCTION()
	void HandleShoppingFinished(AShop* Shop);
	
	UPROPERTY(BlueprintAssignable, Category = "Customer|Event")
	FOnCustomerDestroy OnCustomerDestroy;

	UPROPERTY(BlueprintAssignable, Category = "Customer|Event")
	FOnPurchasedFromShop OnPurchasedFromShop;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Customer")
	void OnPurchasedFromShopBP(int32 MoneySpent);

private:
	bool bIsActive = true;
	bool bIsMakingWay = false;
};
