#include "CustomerViewModel.h"

void UCustomerViewModel::Initialize(ACustomerController* InController)
{
	Controller = InController;
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanStartMakingWay);
	UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanEndMakingWay);
}

void UCustomerViewModel::StartMakingWay()
{
	if (!CanStartMakingWay()) return;

	Controller->StartMakingWay();
	SetIsMakingWay(true);
}

void UCustomerViewModel::EndMakingWay()
{
	if (!CanEndMakingWay()) return;

	Controller->EndMakingWay();
	SetIsMakingWay(false);
}

void UCustomerViewModel::SetIsMakingWay(bool bNewValue)
{
	if (UE_MVVM_SET_PROPERTY_VALUE(bIsMakingWay, bNewValue))
	{
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanStartMakingWay);
		UE_MVVM_BROADCAST_FIELD_VALUE_CHANGED(CanEndMakingWay);
	}
}

bool UCustomerViewModel::CanStartMakingWay() const
{
	return Controller.IsValid() && !bIsMakingWay;
}

bool UCustomerViewModel::CanEndMakingWay() const
{
	return Controller.IsValid() && bIsMakingWay;
}