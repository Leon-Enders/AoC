// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemGlobals.h"
#include "AoCAbilityTypes.h"
#include "AoCComponents/CombatComponent.h"
#include "Interaction/CombatSystemInterface.h"

FGameplayEffectContext* UAoCAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAoCGameplayEffectContext();
}

FGameplayAbilityActorInfo* UAoCAbilitySystemGlobals::AllocAbilityActorInfo() const
{
	return new FAoCGameplayAbilityActorInfo();
}

UCombatComponent* UAoCAbilitySystemGlobals::GetCombatComponentFromActor(AActor* Actor, bool LookForComponent)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}

	const ICombatSystemInterface* CSI = Cast<ICombatSystemInterface>(Actor);
	if (CSI)
	{
		return CSI->GetCombatComponent();
	}

	if (LookForComponent)
	{
		// Fall back to a component search to better support BP-only actors
		return Actor->FindComponentByClass<UCombatComponent>();
	}

	return nullptr;
}


