#include "BasicButton.h"

UBasicButton::UBasicButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// --- Set tween defaults, tweak per widget Blueprint ---
	NormalTween.Color = FLinearColor::White;
	NormalTween.TextColor = FLinearColor::White;
	NormalTween.Scale = FVector2D(1.0, 1.0);
	NormalTween.Offset = FVector2D::ZeroVector;

	HoveredTween.Color = FLinearColor(1.1f, 1.1f, 1.1f, 1.f);
	HoveredTween.TextColor = FLinearColor::White;
	HoveredTween.Scale = FVector2D(1.05, 1.05);
	HoveredTween.Offset = FVector2D(0.0, -2.0);

	PressedTween.Color = FLinearColor(0.75f, 0.75f, 0.75f, 1.f);
	PressedTween.TextColor = FLinearColor::White;
	PressedTween.Scale = FVector2D(0.95, 0.95);
	PressedTween.Offset = FVector2D(0.0, 2.0);

	DisabledTween.Color = FLinearColor(0.4f, 0.4f, 0.4f, 0.6f);
	DisabledTween.TextColor = FLinearColor::White;
	DisabledTween.Scale = FVector2D(1.0, 1.0);
	DisabledTween.Offset = FVector2D::ZeroVector;
}

void UBasicButton::NativeConstruct()
{
	Super::NativeConstruct();

	if (Button)
	{
		Button->OnHovered.AddUniqueDynamic(this, &UBasicButton::HandleHovered);
		Button->OnUnhovered.AddUniqueDynamic(this, &UBasicButton::HandleUnhovered);
		Button->OnPressed.AddUniqueDynamic(this, &UBasicButton::HandlePressed);
		Button->OnReleased.AddUniqueDynamic(this, &UBasicButton::HandleReleased);
		Button->OnClicked.AddUniqueDynamic(this, &UBasicButton::HandleClicked);

		SnapToState(Button->GetIsEnabled() ? NormalTween : DisabledTween);
	}
}

void UBasicButton::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bTweening) return;

	Elapsed += InDeltaTime;
	const float Alpha = (ActiveDuration > KINDA_SMALL_NUMBER)
		? FMath::Clamp(Elapsed / ActiveDuration, 0.f, 1.f)
		: 1.f;

	const float Eased = UKismetMathLibrary::Ease(0.f, 1.f, Alpha, EasingFunc, BlendExp, Steps);

	CurrentState.Color = FMath::Lerp(StartState.Color, TargetState.Color, Eased);
	CurrentState.Scale = FMath::Lerp(StartState.Scale, TargetState.Scale, Eased);
	CurrentState.Offset = FMath::Lerp(StartState.Offset, TargetState.Offset, Eased);
	ApplyCurrent();

	if (Alpha >= 1.f) bTweening = false;
}

// ==================================================
//           Button
// ==================================================

void UBasicButton::TweenToState(const FButtonTweenSettings& Target, float Duration)
{
	StartState = CurrentState; // starts from wherever we are, so interrupted tweens blend smoothly
	TargetState = Target;
	ActiveDuration = (Duration < 0.f) ? TweenDuration : Duration;
	Elapsed = 0.f;

	if (ActiveDuration <= KINDA_SMALL_NUMBER)
	{
		SnapToState(Target);
		return;
	}

	bTweening = true;
}

void UBasicButton::TweenTo(
	FLinearColor TargetColor, FLinearColor TargetTextColor, FVector2D TargetScale, FVector2D TargetOffset, float Duration
)
{
	FButtonTweenSettings TargetTween;
	TargetTween.Color = TargetColor;
	TargetTween.TextColor = TargetTextColor;
	TargetTween.Scale = TargetScale;
	TargetTween.Offset = TargetOffset;
	TweenToState(TargetTween, Duration);
}

void UBasicButton::SnapToState(const FButtonTweenSettings& Target)
{
	bTweening = false;
	CurrentState = Target;
	StartState = Target;
	TargetState = Target;
	ApplyCurrent();
}

void UBasicButton::SetButtonEnabled(bool bEnabled)
{
	if (!Button) return;

	Button->SetIsEnabled(bEnabled);
	if (!bEnabled) TweenToState(DisabledTween);
	else TweenToState(Button->IsHovered() ? HoveredTween : NormalTween);
}

void UBasicButton::ApplyCurrent()
{
	if (Button)
	{
		Button->SetBackgroundColor(CurrentState.Color);
		Button->SetRenderScale(CurrentState.Scale);
		Button->SetRenderTranslation(CurrentState.Offset);
	}

	if (Text)
	{
		Text->SetColorAndOpacity(FSlateColor(CurrentState.TextColor));
	}
}

// ==================================================
//           Events
// ==================================================

void UBasicButton::HandleHovered()
{
	OnButtonHovered.Broadcast();
	TweenToState(HoveredTween);
}

void UBasicButton::HandleUnhovered()
{
	OnButtonUnhovered.Broadcast();
	TweenToState(NormalTween);
}

void UBasicButton::HandlePressed()
{
	TweenToState(PressedTween);
}

void UBasicButton::HandleReleased()
{
	TweenToState((Button && Button->IsHovered()) ? HoveredTween : NormalTween);
}

void UBasicButton::HandleClicked()
{
	OnButtonClicked.Broadcast();
	OnButtonClickedBP();
}