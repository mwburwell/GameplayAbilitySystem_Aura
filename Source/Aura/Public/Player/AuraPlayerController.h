// Copywrite On Draft Mac-N-Cheese

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class IEnemyInterface;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class AURA_API AAuraPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAuraPlayerController();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	// is the Input Mapping Context Blueprint
	// Input Mapping Context records what type of button is pressed
	// WASD and such for player movement
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	// is the AuraInputAction Blueprint
	// Input Action is the type of action being done; boolean, axis1d, axis2d, axis3d
	// MoveAction will fill up with data when an action is pressed, that data needs to
	// be accepted in the Move Function Below hence the FInputActionValue
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	// function for moving the character
	// to bind Move to Actions that provides data
	// we need to include the FInputActionValue
	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;
	
};
