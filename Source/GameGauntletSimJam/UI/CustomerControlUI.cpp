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

	StartButton->OnButtonClicked.AddDynamic(this, &UCustomerControlUI::OnStartClicked);
	EndButton->OnButtonClicked.AddDynamic(this, &UCustomerControlUI::OnEndClicked);

	StartButton->SetButtonText(FText::FromString(MakeWayText));
	StartButton->SetIsEnabled(true);
	EndButton->SetButtonText(FText::FromString(LetInText));
	EndButton->SetIsEnabled(false);
}

void UCustomerControlUI::NativeDestruct()
{
	StartButton->OnButtonClicked.RemoveAll(this);
	EndButton->OnButtonClicked.RemoveAll(this);
	Super::NativeDestruct();
}

void UCustomerControlUI::OnStartClicked()
{
	if (ViewModel) ViewModel->StartMakingWay();

	StartButton->SetIsEnabled(false);
	EndButton->SetIsEnabled(true);
}

void UCustomerControlUI::OnEndClicked()
{
	if (ViewModel) ViewModel->EndMakingWay();

	StartButton->SetIsEnabled(true);
	EndButton->SetIsEnabled(false);
}