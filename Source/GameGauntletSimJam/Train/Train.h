#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Common/Component/LinearMovementComponent.h"
#include "../Customer/Customer.h"
#include "Train.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainTravelUpdate, ATrain*, Train);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainArrived, ATrain*, Train);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTrainHitCustomer, ACustomer*, HitCustomer);

const int32 MaxRandomIteration = 100;

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATrain : public AActor
{
	GENERATED_BODY()
	
public:
	ATrain();

	// ==================================================
	//           Component
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Component")
	ULinearMovementComponent* LinearMovementComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Train|Component")
	USceneComponent* DefaultSceneRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Train|Component")
	UBoxComponent* HitBox;

	// ==================================================
	//           Main
	// ==================================================

	/** How close (in cm) is "close enough" to consider the point reached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Main")
	float AcceptanceRadius = 10.f;

	UFUNCTION(BlueprintCallable, Category = "Train|Main")
	void SetPassTargetLocation(FVector TargetLocation) { PassTargetLocation = TargetLocation; }

	UPROPERTY(BlueprintAssignable, Category = "Train|Main")
	FOnTrainHitCustomer OnTrainHitCustomer;

	// ==================================================
	//           Travel
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Travel")
	float MinTravelDuration = 8.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Travel")
	float MaxTravelDuration = 16.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Travel")
	float TravelUpdateInterval = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Travel")
	/* In Kilometers per hour */
	int32 TrainSpeed = 100;

	UFUNCTION(BlueprintCallable, Category = "Train|Travel")
	/* In Kilometers */
	float GetTrainRemainingDistance() const { return FMath::Max(0.f, TravelTimer) * (TrainSpeed / 3600.f); }

	UPROPERTY(BlueprintAssignable, Category = "Train|Travel")
	FOnTrainTravelUpdate OnTrainTravelUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Train|Travel")
	FOnTrainArrived OnTrainArrived;

	// ==================================================
	//           Pass Through
	// ==================================================

	UFUNCTION(BlueprintCallable, Category = "Train|PassThrough")
	void AllowPassThrough() { PassThrough(); }

	// ==================================================
	//           Naming
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Naming")
	FText TrainType = FText::FromString("Train");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Train|Naming")
	FText TrainCode = FText::FromString("TRN");

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Train|Naming")
	int32 TrainNumber = 0;

	UFUNCTION(BlueprintCallable, Category = "Train|Naming")
	FText GetTrainName() const;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	// ==================================================
	//           Main
	// ==================================================

	void Travel();

	void PassThrough();

	void HandlePointReached();

	UFUNCTION()
	void OnHitBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// ==================================================
	//           Naming
	// ==================================================

	int32 GenerateUniqueNumber() const;

	void ClearUniqueNumber(int32 Number) const;

private:
	bool bIsTraveling = false;
	float TravelTimer;
	float TravelUpdateTimer;

	bool bIsPassing = false;
	FVector PassTargetLocation;

	static TSet<int32> UsedInstanceNumber;

};
