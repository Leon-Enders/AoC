// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemGlobals.h"

#include "AoCAbilityTypes.h"

FGameplayEffectContext* UAoCAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAoCGameplayEffectContext();
}
