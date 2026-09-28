#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BasicMovementComponent.h" // Erase if unused
#include "NavigationMovementComponent.generated.h"

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPointReached);

/**
 * Actor movement using navigation system.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEGAUNTLETSIMJAM_API UNavigationMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNavigationMovementComponent();

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
	//           Move To Point
	// ==================================================

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MoveToPoint")
	FVector FinalTargetlocation = FVector::ZeroVector;

	/** How close (in cm) is "close enough" to consider the point reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveToPoint")
	float AcceptanceRadius = 10.f;

	/** Computes a NavMesh path to TargetLocation, then follows it waypoint by waypoint. */
	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	virtual void MoveToPoint(const FVector& TargetLocation);

	/** Cancels path following and the underlying point movement. */
	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	virtual void StopMovingToPoint();

	UFUNCTION(BlueprintCallable, Category = "MoveToPoint")
	bool IsMovingToPoint() const { return bIsMovingToPoint; }

	/** Broadcast when the owner arrives within AcceptanceRadius of the target. */
	UPROPERTY(BlueprintAssignable, Category = "MoveToPoint")
	FOnPointReached OnPointReached;

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** Runs the NavMesh query and kicks off following the resulting path. */
	void RequestPath(const FVector& TargetLocation);

	/** Moves the path cursor forward and starts the next leg, or finishes if the path is done. */
	void GoToNextWaypoint();

protected:
	FVector CurrentTargetlocation = FVector::ZeroVector;
	TArray<FVector> CurrentPath;
	int32 CurrentPathIndex = INDEX_NONE;
	bool bIsMovingToPoint = false;
};
