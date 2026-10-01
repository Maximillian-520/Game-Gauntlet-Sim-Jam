#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Component/NavigationMovementComponent.h"
#include "CustomerBehaviorComponent.h"
#include "Customer.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UNavigationMovementComponent* NavigationMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
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
	void SeeShop(AShop* Shop);

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void SetExitLocation(const FVector& NewExitLocation) { CustomerBehaviorComponent->SetExitLocation(NewExitLocation); }

	UPROPERTY(BlueprintAssignable, Category = "Customer")
	FOnPurchasedFromShop OnPurchasedFromShop;

	// ==================================================
	//           Event
	// ==================================================
	UFUNCTION()
	void HandleShoppingFinished(AShop* Shop);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GoToExit();

private:
	FVector ExitLocation;

};
