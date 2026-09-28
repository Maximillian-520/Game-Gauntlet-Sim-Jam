#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Component/LinearMovementComponent.h"
#include "Train.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisembarkLocationReached);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisappearLocationReached);

UCLASS()

class GAMEGAUNTLETSIMJAM_API ATrain : public AActor
{
	GENERATED_BODY()
	
public:
	ATrain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	ULinearMovementComponent* LinearMovementComponent;

	UFUNCTION(BlueprintCallable, Category = "Train")
	void GoToDisembarkLocation(const FVector& DisembarkLocation);

	UFUNCTION(BlueprintCallable, Category = "Train")
	void GoToDisappearLocation(const FVector& DisappearLocation);

	UFUNCTION(BlueprintCallable, Category = "Events")
	void HandlePointReached();

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDisembarkLocationReached OnDisembarkLocationReached;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDisappearLocationReached OnDisappearLocationReached;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

public:	
	FVector CurrentTargetLocation;
	bool bGoingToDisembarkLocation = false;
	bool bGoingToDisappearLocation = false;

};
