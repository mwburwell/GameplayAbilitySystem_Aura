// Copywrite On Draft Mac-N-Cheese

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AuraCharacterBases.generated.h"

UCLASS(Abstract)
class AURA_API AAuraCharacterBases : public ACharacter
{
	GENERATED_BODY()

public:
	AAuraCharacterBases();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TObjectPtr<USkeletalMeshComponent> Weapon;
	
};
