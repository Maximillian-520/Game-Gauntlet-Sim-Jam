#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LinearMovementComponent.generated.h"

/**
 * Linear actor movement on linear in a straight line along a direction vector.
 * Speed ramps up toward MoveSpeed via Forward() and down toward 0 via Brake().
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEGAUNTLETSIMJAM_API ULinearMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULinearMovementComponent();

	// ==================================================
	//           Movement Settings
	// ==================================================

	/** Maximum speed in units per second. Velocity is clamped to this value. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MovementSettings")
	float MoveSpeed = 300.f;

	// ==================================================
	//           Linear Movement
	// ==================================================

	/** Rate (units/sec^2) at which speed increases toward MoveSpeed while Forward() is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinearMovement")
	float Acceleration = 100.f;

	/** Rate (units/sec^2) at which speed decreases toward 0 while Brake() is called. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LinearMovement")
	float BrakeDeceleration = 100.f;

	/** Speeds up toward MoveSpeed using Acceleration. Call every frame while forward input is held. */
	UFUNCTION(BlueprintCallable, Category = "LinearMovement")
	virtual void Forward();

	/** Slows toward 0 using BrakeDeceleration. Call every frame while brake input is held. */
	UFUNCTION(BlueprintCallable, Category = "LinearMovement")
	virtual void Brake();

	UFUNCTION(BlueprintCallable, Category = "LinearMovement")
	bool IsMoving() const { return Velocity > 0; }

	/** Sets the world-space direction of travel. */
	UFUNCTION(BlueprintCallable, Category = "LinearMovement")
	virtual void SetDirection(const FVector& NewDirection) { Direction = NewDirection.GetSafeNormal(); }

	/** Sets the current speed directly, clamped between 0 and MoveSpeed. */
	UFUNCTION(BlueprintCallable, Category = "LinearMovement")
	virtual void SetVelocity(float NewVelocity) { Velocity = FMath::Clamp(NewVelocity, 0.f, MoveSpeed); }

	UFUNCTION(BlueprintPure, Category = "LinearMovement")
	float GetVelocity() const { return Velocity; }

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FVector Direction;
	float Velocity;

};