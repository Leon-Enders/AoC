// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCAbilityTargetActor_MeleeScan.h"
#include "Abilities/GameplayAbility.h"

AAoCAbilityTargetActor_MeleeScan::AAoCAbilityTargetActor_MeleeScan(const FObjectInitializer& ObjectInitializer)
{
	
}


void AAoCAbilityTargetActor_MeleeScan::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FGameplayAbilityTargetDataHandle AAoCAbilityTargetActor_MeleeScan::MakeTargetData(
	const TArray<FHitResult>& HitResults) const
{
	if (OwningAbility)
	{
		/** Use the source location instead of the literal origin */
		return StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility,HitResults);
	}

	return FGameplayAbilityTargetDataHandle();
}
