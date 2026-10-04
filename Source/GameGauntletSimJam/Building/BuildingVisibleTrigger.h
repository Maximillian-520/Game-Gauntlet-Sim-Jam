#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../Customer/Customer.h"
#include "./Plot/Plot.h"
#include "BuildingVisibleTrigger.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ABuildingVisibleTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingVisibleTrigger();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere)
    UBoxComponent* TriggerBox;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger")
    TArray<TObjectPtr<APlot>> Plots;

    UFUNCTION()
    void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

};
