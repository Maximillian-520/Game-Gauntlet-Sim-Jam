#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Common/Component/LinearMovementComponent.h"
#include "../Customer/Customer.h"
#include "Train.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainHitCustomer, ACustomer*, HitCustomer);

UCLASS()


class GAMEGAUNTLETSIMJAM_API ATrain : public AActor
{
	GENERATED_BODY()
	
public:
	ATrain();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	ULinearMovementComponent* LinearMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* HitBox;

	/** How close (in cm) is "close enough" to consider the point reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train")
	float AcceptanceRadius = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train")
	float MinTravelDuration = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train")
	float MaxTravelDuration = 16.f;

	UFUNCTION(BlueprintCallable, Category = "Train")
	void SetPassTargetLocation(FVector TargetLocation) { PassTargetLocation = TargetLocation; }

	UPROPERTY(BlueprintAssignable, Category = "Train")

	FOnTrainHitCustomer OnTrainHitCustomer;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void Travel();

	void PassThrough();

	void HandlePointReached();

	UFUNCTION()
	void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	bool bIsTraveling = false;
	float TravelTimer;

	bool bIsPassing = false;
	FVector PassTargetLocation;

};
