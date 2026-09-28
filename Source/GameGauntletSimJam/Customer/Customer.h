#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Component/NavigationMovementComponent.h"
#include "CustomerBehaviorComponent.h"

#include "Customer.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ACustomer : public AActor
{
	GENERATED_BODY()

public:
	ACustomer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UNavigationMovementComponent* NavigationMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UCustomerBehaviorComponent* CustomerBehaviorComponent;

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void SeeShop(AShop* Shop);

	UFUNCTION(BlueprintCallable, Category = "Customer")
	void SetExitLocation(const FVector& NewExitLocation) { CustomerBehaviorComponent->SetExitLocation(NewExitLocation); }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void GoToExit();

private:
	FVector ExitLocation;

};
