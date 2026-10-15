#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MVVMSubsystem.h"
#include "View/MVVMView.h"
#include "../Customer/CustomerController.h"
#include "./Component/BasicButton.h"
#include "./ViewModel/CustomerViewModel.h"
#include "CustomerControlUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UCustomerControlUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	const FString MakeWayText = "Make Way";
	const FString LetInText = "Let In";

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBasicButton> EndButton;

private:
	UPROPERTY()
	TObjectPtr<UCustomerViewModel> ViewModel;

	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnEndClicked();

};
