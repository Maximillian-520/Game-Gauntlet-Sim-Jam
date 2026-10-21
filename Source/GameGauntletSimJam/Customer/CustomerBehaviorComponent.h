#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Common/Component/CrowdMovementComponent.h"
#include "../Building/Shop/Shop.h"
#include "CustomerBehaviorComponent.generated.h"

UENUM(BlueprintType)
enum class EBehaviorState : uint8
{
	/** Default idle state */
	Idle        UMETA(DisplayName = "Idle"),
	/** Strolling the market towards intended exit */
	Strolling   UMETA(DisplayName = "Strolling"),
	/** Going and shopping in target shop */
	Shopping	UMETA(DisplayName = "Shopping"),
	/** Find nearest exit (not to exit) to make way for train */
	MakingWay	UMETA(DisplayName = "MakingWay"),
	/** Disabled state */
	Disabled    UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCustomerExited);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnShoppingFinished, AShop*, Shop);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEGAUNTLETSIMJAM_API UCustomerBehaviorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCustomerBehaviorComponent();

	UPROPERTY()
	TObjectPtr<UCrowdMovementComponent> MovementComponent;

	// ==================================================
	//           State
	// ==================================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	EBehaviorState State = EBehaviorState::Idle;

	UFUNCTION(BlueprintCallable, Category = "Behavior")
	void ChangeState(EBehaviorState NewState);

	// ==================================================
	//           Strolling
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Behavior|Strolling")
	void SetExit(AActor* NewExitActor, const FVector& NewExitLocation, const FRotator& NewExitRotation);

	UPROPERTY(BlueprintAssignable, Category = "Behavior|Strolling")
	FOnCustomerExited OnCustomerExited;

	// ==================================================
	//           Shopping
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior|Shopping")
	float MinPeekingDuration = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior|Shopping")
	float MaxPeekingDuration = 3.0f;

	UFUNCTION(BlueprintCallable, Category = "Behavior|Shopping")
	void GoToShop(AShop* Shop);

	UPROPERTY(BlueprintAssignable, Category = "Behavior|Shopping")
	FOnShoppingFinished OnShoppingFinished;

	// ==================================================
	//           Making Way
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior|Making Way")
	float MinPatienceDuration = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior|Making Way")
	float MaxPatienceDuration = 15.0f;

	UFUNCTION(BlueprintCallable, Category = "Behavior|Making Way")
	void DoMakeWay(AActor* NewMakeWayActor, const FVector& NewMakeWayLocation, const FRotator& NewMakeWayRotation);

	UFUNCTION(BlueprintCallable, Category = "Behavior|Making Way")
	bool IsMakingWay() const { return State == EBehaviorState::MakingWay; }

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
	FRotator ExitRotation;
	
	// Shopping
	TObjectPtr<AShop> TargetShop;
	bool bHasReachedShop = false;
	float ShopPeekTimer;

	// Making Way
	AActor* MakeWayActor;
	FVector MakeWayLocation;
	FRotator MakeWayRotation;
	bool bHasMadeWay = false;
	float MakeWayPatienceTimer;

};
