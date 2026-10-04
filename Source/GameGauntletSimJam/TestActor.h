#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestActor.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API ATestActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ATestActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	float TestVar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	FVector TestVector;

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:	

};
