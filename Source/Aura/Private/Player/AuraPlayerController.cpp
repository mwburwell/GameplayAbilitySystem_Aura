// Copywrite On Draft Mac-N-Cheese


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"

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
