// Copyright MacNChzOnDraft


#include "Character/AuraEnemy.h"
#include "DrawDebugHelpers.h"

void AAuraEnemy::HighlightActor()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 300.f, 8, FColor::Red);
}

void AAuraEnemy::UnHighlightActor()
{
}
