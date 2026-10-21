#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "../Component/BasicButton.h"
#include "MenuUI.generated.h"

UCLASS()
class GAMEGAUNTLETSIMJAM_API UMenuUI : public UUserWidget
{
	GENERATED_BODY()

public:
	/** Level opened when Start is pressed. Set this in the widget Blueprint's class defaults. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu")
	FName GameLevelName = TEXT("GameMap");

protected:
	virtual void NativeConstruct() override;

	const FString StartText = "Start";
	const FString QuitText = "Quit";

	UPROPERTY(meta = (BindWidget))
	UBasicButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	UBasicButton* QuitButton;

private:
	UFUNCTION()
	void Start();

	UFUNCTION()
	void Quit();
};
