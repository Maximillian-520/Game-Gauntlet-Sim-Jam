#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicMovementComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPointReached);

/**
 * Simple basic component for actor movement with
 * WASD / point and click movement.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEGAUNTLETSIMJAM_API UBasicMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBasicMovementComponent();

	// ==================================================
	//           Movement Settings
	// ==================================================

	/** Units per second the actor moves. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementSettings")
	float MoveSpeed = 300.f;

	/** If true, the owner rotates smoothly to face its movement direction. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementSettings")
	bool bRotateToFaceMovement = true;

	/** Degrees per second used to rotate the actor to face move direction, if bRotateToFaceMovement is true. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementSettings")
	float RotationSpeed = 360.f;

	// ==================================================
	//           WASD Movement
	// ==================================================

	/** Call this each frame with the forward/backward input axis value */
	UFUNCTION(BlueprintCallable, Category = "WASDMovement")
	void MoveForward(float Value);

	/** Call this each frame with the right/left input axis value */
	UFUNCTION(BlueprintCallable, Category = "WASDMovement")
	void MoveRight(float Value);

	// ==================================================
	//           Move To Point
	// ==================================================

	/** Begin moving the owner toward TargetLocation. */
	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	virtual void MoveToPoint(const FVector& TargetLocation);

	/** Stop moving immediately. */
	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	virtual void StopMovingToPoint();

	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	bool IsMovingToPoint() const { return bIsMovingToPoint; }
	
	/** How close (in cm) is "close enough" to consider the point reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveToPoint")
	float AcceptanceRadius = 10.f;

	/** Broadcast when the owner arrives within AcceptanceRadius of the target. */
	UPROPERTY(BlueprintAssignable, Category = "MoveToPoint")
	FOnPointReached OnPointReached;

	// ==================================================
	//           Direction Movement
	// ==================================================

	/** Begin moving the owner toward TargetLocation. */
	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	void MoveToDirection(const FVector& Direction);

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	// WASD movement
	float ForwardInputValue = 0.f;
	float RightInputValue = 0.f;

	// Move to point
	FVector CurrentTargetlocation = FVector::ZeroVector;
	bool bIsMovingToPoint = false;

	// Direction movement
	FVector CurrentFrameMoveDirection;
};