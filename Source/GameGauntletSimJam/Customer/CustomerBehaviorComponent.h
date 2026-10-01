#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Component/NavigationMovementComponent.h"
#include "../Shop/Shop.h"
#include "CustomerBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Exiting      UMETA(DisplayName = "Exiting"),
	Shopping     UMETA(DisplayName = "Shopping"),
	Disabled    UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShoppingFinished, AShop*, Shop);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEGAUNTLETSIMJAM_API UCustomerBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCustomerBehaviorComponent();

	UPROPERTY()
	TObjectPtr<UNavigationMovementComponent> NavMovement;

	// ==================================================
	//           State
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "State")
	EBehaviorState State = EBehaviorState::Idle;

	UFUNCTION(BlueprintCallable, Category = "State")
	void ChangeState(EBehaviorState NewState);

	// ==================================================
	//           Exiting
	// ==================================================

	void SetExitLocation(const FVector& NewExitLocation) { ExitLocation = NewExitLocation; }

	// ==================================================
	//           Shopping
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
	float MinPeekingDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shopping")
	float MaxPeekingDuration = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "Shopping")
	void GoToShop(AShop* Shop);

	UPROPERTY(BlueprintAssignable, Category = "Shopping")
	FOnShoppingFinished OnShoppingFinished;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// ==================================================
	//           State
	// ==================================================
	
	void EnterState(EBehaviorState EnterState);

	void ExitState(EBehaviorState ExitState);

	void UpdateState(float DeltaTime);

	// ==================================================
	//           Event
	// ==================================================

	UFUNCTION()
	void HandlePointReached();

private:
	// Exiting
	FVector ExitLocation;
	
	// Shopping
	TObjectPtr<AShop> TargetShop;
	bool bHasReachedShop = false;
	float ShopPeekTimer;

};
