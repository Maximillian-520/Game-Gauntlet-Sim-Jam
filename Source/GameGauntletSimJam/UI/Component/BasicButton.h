#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/EngineTypes.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "BasicButton.generated.h"

USTRUCT(BlueprintType)
struct FButtonTweenSettings
{
	GENERATED_BODY()

	/** Change button color through Button->SetBackgroundColor*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
	FLinearColor Color = FLinearColor::White;

	/** Change text color through Text->SetColorAndOpacity (if text exist)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
	FLinearColor TextColor = FLinearColor::White;

	/** Render scale of the button. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
	FVector2D Scale = FVector2D(1.0, 1.0);

	/** Render-space translation offset (in slate units) from the button's resting position. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tween")
	FVector2D Offset = FVector2D::ZeroVector;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);

/**
 * Basic button component for UI.
 */
UCLASS()
class GAMEGAUNTLETSIMJAM_API UBasicButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UBasicButton(const FObjectInitializer& ObjectInitializer);

	// ==================================================
	//           Button
	// ==================================================

	/** Tween to a full state over Duration (uses TweenDuration if Duration < 0). */
	UFUNCTION(BlueprintCallable, Category = "Button")
	void TweenToState(const FButtonTweenSettings& Target, float Duration = -1.f);

	/** Tween to explicit values. */
	UFUNCTION(BlueprintCallable, Category = "Button")
	void TweenTo(
		FLinearColor TargetColor, FLinearColor TargetTextColor, FVector2D TargetScale, FVector2D TargetOffset, float Duration = -1.f
	);

	/** Jump to a state immediately and cancel any running tween. */
	UFUNCTION(BlueprintCallable, Category = "Button")
	void SnapToState(const FButtonTweenSettings& Target);

	/** Enables/disables the button and tweens to the matching state. */
	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetButtonEnabled(bool bEnabled);

	/** Sets Text widget text content. */
	UFUNCTION(BlueprintCallable, Category = "Button")
	void SetButtonText(const FText NewText) { if (Text) Text->SetText(NewText); }

	UFUNCTION(BlueprintPure, Category = "Button")
	bool IsTweening() const { return bTweening; }

	/** Fired when the inner button is clicked. */
	UPROPERTY(BlueprintAssignable, Category = "Button")
	FOnButtonClicked OnButtonClicked;
	UFUNCTION(BlueprintImplementableEvent, Category = "Button")
	void OnButtonClickedBP();

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	// ==================================================
	//           Component
	// ==================================================

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Button|Component")
	UButton* Button;

	UPROPERTY(VisibleAnywhere, meta = (BindWidgetOptional))
	UTextBlock* Text;

	// ==================================================
	//           Tween
	// ==================================================

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Tween")
	FButtonTweenSettings NormalTween;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Tween")
	FButtonTweenSettings HoveredTween;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Tween")
	FButtonTweenSettings PressedTween;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Tween")
	FButtonTweenSettings DisabledTween;

	// ==================================================
	//           Easing
	// ==================================================

	/** Default tween time in seconds. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Easing", meta = (ClampMin = "0.0"))
	float TweenDuration = 0.15f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Easing")
	TEnumAsByte<EEasingFunc::Type> EasingFunc = EEasingFunc::EaseOut;

	/** Exponent for Ease In/Out/InOut functions. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Easing")
	float BlendExp = 2.f;

	/** Step count for the Step easing function. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Button|Easing")
	int32 Steps = 2;

private:
	FButtonTweenSettings CurrentState;
	FButtonTweenSettings StartState;
	FButtonTweenSettings TargetState;

	float Elapsed = 0.f;
	float ActiveDuration = 0.f;
	bool bTweening = false;

	// --- Events ---
	UFUNCTION() void HandleHovered();
	UFUNCTION() void HandleUnhovered();
	UFUNCTION() void HandlePressed();
	UFUNCTION() void HandleReleased();
	UFUNCTION() void HandleClicked();

	void ApplyCurrent();
};
