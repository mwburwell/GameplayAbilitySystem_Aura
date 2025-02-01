// Copywrite On Draft Mac-N-Cheese


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// if aura context input mapping is not set then crash the game
	check(AuraContext);

	// get the local player's subsytem and if it is not available crash the game
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	// add the mapping context provided through blueprint to this subsystem
	//
	// priority: if we have multiple input mapping contexts and they are competing
	// for the same input then we will look at who has the higher priority.
	// AuraContext has a priority of 0 because we do not plan on having other contexts
	//
	// example: if a player get's drunk then you can add another mapping context with
	// a higher priority that may randomize the input mapping
	// making it seem like you are staggering
	Subsystem->AddMappingContext(AuraContext, 0);

	// options for the mouse viability and UI
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
	
	
}

// used to be in the AuraCharacterBase
void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// The Player Controller base class comes with an InputComponent, but we created an
	// EnhancedInputComponent in BeginPlay(). Player Controller's Input Componenent needs
	// to be cast to EnhancedInputComponent and Crash the game if we can't
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// binds our MoveAction to the Move Function through the EnhancedInputComponent
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// InputActionValue is the argument recieved from the MoveAction
	// we need the input action in a value of Vector2D for WASD
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();

	// To decide what is forward we need to figure out what forward is
	// GetConrolRotation() gives the full aim rotation, which in our case
	// is the direction from the camera to the character
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.0f);

	// normalized directions based on the rotation of the camera facing the
	// player where the pitch and roll are zeroed out
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// get pawn and move them based on the Input Actions
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
