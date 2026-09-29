#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Component/LinearMovementComponent.h"
#include "Train.generated.h"

UCLASS()

class GAMEGAUNTLETSIMJAM_API ATrain : public AActor
{
	GENERATED_BODY()
	
public:
	ATrain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	ULinearMovementComponent* LinearMovementComponent;

	/** How close (in cm) is "close enough" to consider the point reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train")
	float AcceptanceRadius = 10.f;

	UFUNCTION(BlueprintCallable, Category = "Train")
	void GoToLocation(FVector NewTargetLocation);

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void HandlePointReached();

public:
	bool bIsMoving = false;
	FVector TargetLocation;

};
