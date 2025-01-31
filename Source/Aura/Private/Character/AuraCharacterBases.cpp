// Copywrite On Draft Mac-N-Cheese


#include "Character/AuraCharacterBases.h"

AAuraCharacterBases::AAuraCharacterBases()
{
	PrimaryActorTick.bCanEverTick = true;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AAuraCharacterBases::BeginPlay()
{
	Super::BeginPlay();
	
}

