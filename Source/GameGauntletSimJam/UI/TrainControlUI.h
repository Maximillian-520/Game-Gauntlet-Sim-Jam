#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "./ViewModel/TrainViewModel.h"
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
	UTrainNotificationUI* SpawnOrUpdateNotification(const FText& TrainName, const FText& Message);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void RemoveNotification(const FText& TrainName);
	void RemoveNotification(UTrainNotificationUI* NotificationUI);

protected:
	virtual void NativeConstruct() override;

	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* NotificationBox;

private:
	UPROPERTY()
	TObjectPtr<UTrainViewModel> ViewModel;

	UPROPERTY()
	TMap<FName, UTrainNotificationUI*> TrainNotificationMap;

	UFUNCTION()
	void HandleNotificationRequested(const FText& TrainName, const FText& Message);

	UFUNCTION()
	void HandleNotificationDeleted(const FText& TrainName);

};
