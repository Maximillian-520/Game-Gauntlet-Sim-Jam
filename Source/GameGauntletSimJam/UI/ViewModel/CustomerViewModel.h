#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "../../Customer/CustomerController.h"
#include "CustomerViewModel.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UCustomerViewModel : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	void Initialize(ACustomerController* InController);

	UFUNCTION(BlueprintCallable, Category = "CustomerControl")
	void StartMakingWay();

	UFUNCTION(BlueprintCallable, Category = "CustomerControl")
	void EndMakingWay();

	void SetIsMakingWay(bool bNewValue);
	bool GetIsMakingWay() const { return bIsMakingWay; }

	// Derived state the buttons bind to
	UFUNCTION(BlueprintPure, FieldNotify, Category = "CustomerControl")
	bool CanStartMakingWay() const;

	UFUNCTION(BlueprintPure, FieldNotify, Category = "CustomerControl")
	bool CanEndMakingWay() const;

private:
	UPROPERTY(BlueprintReadOnly, FieldNotify, Setter = SetIsMakingWay, Getter = GetIsMakingWay, meta = (AllowPrivateAccess = "true"))
	bool bIsMakingWay = false;

	TWeakObjectPtr<ACustomerController> Controller;
};