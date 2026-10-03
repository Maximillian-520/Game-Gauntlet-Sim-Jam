#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "../Common/ViewModel/TrainViewModel.h"
#include "./Parts/TrainNotificationUI.h"
#include "TrainControlUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UTrainControlUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UTrainNotificationUI> TrainNotificationUIBlueprint;

	UFUNCTION(BlueprintCallable, Category = "UI")
	UTrainNotificationUI* SpawnNotification(const FText& Message);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* NotificationBox;

private:
	TObjectPtr<UTrainViewModel> ViewModel;

	UFUNCTION()
	void HandleNotificationRequested(const FText& Message);

	void RemoveNotification(UTrainNotificationUI* Notification);

};
