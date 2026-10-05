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
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetMessage(const FText& Message);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void Disappear();

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MessageText;

	UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
	UWidgetAnimation* FadeAnim;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	bool bIsMarkedForDestoy = false;

private:
	
};