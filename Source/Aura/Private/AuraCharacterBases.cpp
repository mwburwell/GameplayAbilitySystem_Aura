// Copywrite On Draft Mac-N-Cheese


#include "AuraCharacterBases.h"

// Sets default values
AAuraCharacterBases::AAuraCharacterBases()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAuraCharacterBases::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAuraCharacterBases::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAuraCharacterBases::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

