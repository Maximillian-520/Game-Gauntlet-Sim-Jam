#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "Engine/World.h"
#include "NavigationMovementComponent.h"
#include "CrowdMovementComponent.generated.h"

/**
 * Navigation movement with natural crowd variation:
 *  - per-agent speed variance
 *  - per-trip lane offset (path points shifted sideways, kept on the NavMesh)
 *  - scattered final destination so agents don't stack on one point
 *  - randomized acceptance radius on intermediate waypoints (corner cutting)
 *  - sideways wobble while walking
 *  - separation from other crowd agents
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEGAUNTLETSIMJAM_API UCrowdMovementComponent : public UNavigationMovementComponent
{
	GENERATED_BODY()

public:
	UCrowdMovementComponent();

	// ==================================================
	//           Speed
	// ==================================================

	/** MoveSpeed is multiplied once at BeginPlay by a random value in this range. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Speed")
	FVector2D SpeedMultiplierRange = FVector2D(0.85f, 1.15f);

	// ==================================================
	//           Path variation
	// ==================================================

	/** Max sideways shift (cm) of intermediate path points. Rolled once per trip, so each agent keeps its own "lane". */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Path", meta = (ClampMin = "0"))
	float MaxLaneOffset = 80.f;

	/** Radius (cm) around the final destination in which each agent picks its own arrival spot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Path", meta = (ClampMin = "0"))
	float FinalScatterRadius = 80.f;

	/** Search extent used to keep shifted points on the NavMesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Path")
	FVector NavProjectionExtent = FVector(150.f, 150.f, 250.f);

	/** Acceptance radius (cm) rolled randomly per intermediate waypoint, so agents cut corners at different points. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Path")
	FVector2D IntermediateAcceptanceRadiusRange = FVector2D(40.f, 120.f);

	/** Acceptance radius (cm) for the last waypoint. Keep small, the base class snaps to the target on arrival. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Path", meta = (ClampMin = "0"))
	float FinalAcceptanceRadius = 10.f;

	/** Moves path points to the actor's current height so NavMesh-vs-pivot Z differences can't stall arrival. Disable for sloped or multi-level maps. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Path")
	bool bFlattenPathToActorHeight = true;

	// ==================================================
	//           Wobble
	// ==================================================

	/** Peak sideways sway (cm) while walking. Set 0 to disable. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Wobble", meta = (ClampMin = "0"))
	float WobbleAmplitude = 12.f;

	/** Sway speed in radians per second. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Wobble", meta = (ClampMin = "0"))
	float WobbleFrequency = 1.8f;

	/** Wobble fades out within this distance (cm) of the destination so arrival stays clean. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Wobble", meta = (ClampMin = "1"))
	float ArrivalFadeDistance = 200.f;

	// ==================================================
	//           Separation
	// ==================================================

	/** Agents closer than this (cm) push each other apart. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Separation", meta = (ClampMin = "0"))
	float SeparationRadius = 100.f;

	/** Max push speed (cm/s) from separation. Keep well below MoveSpeed so agents still arrive. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Crowd|Separation", meta = (ClampMin = "0"))
	float SeparationStrength = 120.f;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void RequestPath(const FVector& TargetLocation) override;

	virtual void GoToNextWaypoint() override;

private:
	/** Phase so agents don't sway in sync. */
	float AgentPhase = 0.f;

	/** Registry of live agents, avoids per-tick GetAllActorsOfClass. */
	static TArray<UCrowdMovementComponent*> ActiveAgents;

	/** Shifts intermediate points sideways and scatters the final point, keeping everything on the NavMesh. */
	void ApplyCrowdOffsetsToPath();

	/** Final waypoint uses FinalAcceptanceRadius, intermediate ones a random radius from the range. */
	void UpdateAcceptanceRadiusForLeg();

	/** Horizontal push away from nearby crowd agents (cm/s). */
	FVector ComputeSeparation(const FVector& MyLocation) const;

};