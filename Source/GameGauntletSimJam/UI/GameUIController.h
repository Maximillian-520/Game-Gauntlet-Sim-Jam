#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoneyUI.h"
#include "GameUIController.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API AGameUIController : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameUIController();

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMoneyUI> MoneyUIBlueprint;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	UMoneyUI* MoneyUIWidget;
};
