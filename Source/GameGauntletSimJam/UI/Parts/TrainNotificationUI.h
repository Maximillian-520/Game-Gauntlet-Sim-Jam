#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Animation/WidgetAnimation.h"
#include "TimerManager.h"
#include "TrainNotificationUI.generated.h"

class UTextBlock;

UCLASS()
class GAMEGAUNTLETSIMJAM_API UTrainNotificationUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	float NotificationDuration = 3.0f;

	UPROPERTY(EditAnywhere, Category = "UI")
	FText NotificationMessage = FText::FromString("Train Notification");

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MessageText;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* FadeAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	bool bIsMarkedForDestoy = false;

private:
	FTimerHandle DisappearTimer;

	void Disappear();
};