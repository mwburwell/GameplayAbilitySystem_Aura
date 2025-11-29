// Copyright MacNChzOnDraft


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return ;

	LastActor = ThisActor; 
	ThisActor = CursorHit.GetActor();

	/**
	 *	Case A: Last Actor is null && This Actor is null
	 *		- Do Nothing
	 *	Case B: Last Actor is null && This Actor is valid
	 *		- Hightlight This Actor
	 *	Case C: Last Actor is Valid && This Actor is null
	 *		- UnHighlight Last Actor
	 *	Case D: Both are Valid and Different
	 *		- UnHighlight Last Actor
	 *		- Highlight This Actor
	 *	Case E: Both are Valid and the Same
	 *		- Do Nothing
	 */

	if (LastActor == nullptr)
	{
		if (ThisActor == nullptr)
		{
			// Case A: Do Nothing
		}
		else
		{
			// Case B
			ThisActor->HighlightActor();
		}
	}
	else
	{
		if (ThisActor == nullptr)
		{
			// Case C
			LastActor->UnHighlightActor();
		}
		else
		{
			if (ThisActor != LastActor)
			{
				// Case D
				LastActor->UnHighlightActor();
				ThisActor->HighlightActor();
			}
			else
			{
				// Case E: Do Nothing
			}
		}
	}
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);
	Subsystem->AddMappingContext(AuraContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	FInputModeGameAndUI InputModeGameAndUI;
	InputModeGameAndUI.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeGameAndUI.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeGameAndUI);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxis = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxis.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxis.X);
	}

	
}
