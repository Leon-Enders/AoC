// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemGlobals.h"

#include "AoCAbilityTypes.h"
#include "AoCComponents/CombatComponent.h"
#include "Interaction/CombatSystemInterface.h"

FGameplayEffectContext* UAoCAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAoCGameplayEffectContext();
}

UCombatComponent* UAoCAbilitySystemGlobals::GetCombatComponentFromActor(const AActor* Actor, bool LookForComponent)
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
		return Actor->FindComponentByClass<UCombatComponent>();
	}

	return nullptr;

}
