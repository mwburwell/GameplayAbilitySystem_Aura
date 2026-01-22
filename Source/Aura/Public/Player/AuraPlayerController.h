// Copyright MacNChzOnDraft

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerController.generated.h"

class USplineComponent;
class IEnemyInterface;
class UInputAction;
class UInputMappingContext;
class UAuraInputConfig;
class UAuraAbilitySystemComponent;
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
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	/**
	 * Move: 
	 * @param InputActionValue 
	 */
	void Move(const FInputActionValue& InputActionValue);


	/**
	 * Input Configuration for Abilities
	 */
	/**
	 * 
	 * @param InputTag 
	 */
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	/**
	 * Cursor
	 */
	
	void CursorTrace();
	FHitResult CursorHit;
	
	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	/**
	 * Click to Move
	 */
	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.0f;
	float ShortPressThreshold = 0.9f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float AutoRunAcceptanceRadius = 50.0f;

	TObjectPtr<USplineComponent> AutoRunSpline;

	void AutoRun();
};
