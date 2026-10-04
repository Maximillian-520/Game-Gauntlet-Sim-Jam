#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "MVVMSubsystem.h"
#include "View/MVVMView.h"
#include "../Customer/CustomerController.h"
#include "./ViewModel/CustomerViewModel.h"
#include "CustomerControlUI.generated.h"

class UButton;
class UCustomerControlViewModel;

UCLASS()
class GAMEGAUNTLETSIMJAM_API UCustomerControlUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> EndButton;

private:
	UPROPERTY()
	TObjectPtr<UCustomerViewModel> ViewModel;

	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnEndClicked();

};
