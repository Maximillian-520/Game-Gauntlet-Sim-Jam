#include "TestActor.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("DebugPrint"));
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *TestVector.ToString());

	//TArray<AActor*> Actors;
	//for (AActor* Actor : Actors)
	//{
	//	// Content
	//}
}

void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

