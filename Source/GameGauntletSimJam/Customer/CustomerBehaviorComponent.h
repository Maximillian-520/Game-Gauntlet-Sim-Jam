#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Common/Component/NavigationMovementComponent.h"
#include "../Shop/Shop.h"
#include "CustomerBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorState : uint8
{
	Idle        UMETA(DisplayName = "Idle"),
	Strolling   UMETA(DisplayName = "Strolling"),
	Shopping	UMETA(DisplayName = "Shopping"),
	MakingWay	UMETA(DisplayName = "MakingWay"),
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	EBehaviorState State = EBehaviorState::Idle;

	UFUNCTION(BlueprintCallable, Category = "State")
	void ChangeState(EBehaviorState NewState);

	// ==================================================
	//           Strolling
	// ==================================================

	void SetExit(AActor* NewExitActor, const FVector& NewExitLocation);

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

	// ==================================================
	//           Making Way
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Making Way")
	float MinPatienceDuration = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Making Way")
	float MaxPatienceDuration = 15.0f;

	UFUNCTION(BlueprintCallable, Category = "Making Way")
	void DoMakeWay(AActor* NewMakeWayActor, const FVector& NewMakeWayLocation);

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
	// Strolling
	AActor* ExitActor;
	FVector ExitLocation;
	
	// Shopping
	TObjectPtr<AShop> TargetShop;
	bool bHasReachedShop = false;
	float ShopPeekTimer;

	// Making Way
	AActor* MakeWayActor;
	FVector MakeWayLocation;
	bool bHasMadeWay = false;
	float MakeWayPatienceTimer;

};
