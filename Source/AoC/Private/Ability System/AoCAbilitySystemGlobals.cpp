// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemGlobals.h"
#include "AoCAbilityTypes.h"

FGameplayEffectContext* UAoCAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAoCGameplayEffectContext();
}

FGameplayAbilityActorInfo* UAoCAbilitySystemGlobals::AllocAbilityActorInfo() const
{
	return new FAoCGameplayAbilityActorInfo();
}