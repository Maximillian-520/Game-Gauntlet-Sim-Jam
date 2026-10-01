#include "CustomerControlUI.h"

void UCustomerControlUI::NativeConstruct()
{
	Super::NativeConstruct();

	ViewModel = NewObject<UCustomerViewModel>(this);

	if (ACustomerController* Controller = Cast<ACustomerController>(
		UGameplayStatics::GetActorOfClass(this, ACustomerController::StaticClass())))
	{
		ViewModel->Initialize(Controller);
	}

	// Hand the ViewModel to the MVVM view so the Bindings tab can see it
	if (UMVVMView* View = UMVVMSubsystem::GetViewFromUserWidget(this))
	{
		View->SetViewModelByClass(ViewModel);
	}

	StartButton->OnClicked.AddDynamic(this, &UCustomerControlUI::OnStartClicked);
	EndButton->OnClicked.AddDynamic(this, &UCustomerControlUI::OnEndClicked);
}

void UCustomerControlUI::NativeDestruct()
{
	StartButton->OnClicked.RemoveAll(this);
	EndButton->OnClicked.RemoveAll(this);
	Super::NativeDestruct();
}

void UCustomerControlUI::OnStartClicked()
{
	if (ViewModel) ViewModel->StartMakingWay();
}

void UCustomerControlUI::OnEndClicked()
{
	if (ViewModel) ViewModel->EndMakingWay();
}