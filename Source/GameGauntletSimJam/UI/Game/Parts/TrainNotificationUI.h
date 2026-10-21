
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "TimerManager.h"
#include "TrainNotificationUI.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNotificationUpdate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNotificationDisappear);

UCLASS()
class GAMEGAUNTLETSIMJAM_API UTrainNotificationUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void Show(const FText& TrainType, const FText& TrainName, const FText& Status);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Update(const FText& Status);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Disappear();

protected:
	const FString IncomingText = "Incoming {0}: {1}";

	UPROPERTY(meta = (BindWidget))
	UTextBlock* IncomingTrainText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StatusText;

	/** Connects animaton from OnNotificationDisappear */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bHasDisappearAnimation = false;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnNotificationUpdate OnNotificationUpdate;

	UPROPERTY(BlueprintAssignable, Category = "Event")
	FOnNotificationDisappear OnNotificationDisappear;

private:
	
};