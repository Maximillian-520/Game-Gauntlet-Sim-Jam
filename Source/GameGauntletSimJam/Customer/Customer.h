#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Component/NavigationMovementComponent.h"

#include "Customer.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomer : public AActor
{
	GENERATED_BODY()

public:
	ACustomer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UNavigationMovementComponent* NavigationMovementComponent;

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void SetExitLocation(const FVector& NewExitLocation) { ExitLocation = NewExitLocation; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GoToExit();

private:
	FVector ExitLocation;

};
