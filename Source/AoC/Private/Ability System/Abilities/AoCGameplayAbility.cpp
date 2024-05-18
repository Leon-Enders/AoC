// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "AoCAbilityTypes.h"

const FAoCGameplayAbilityActorInfo* UAoCGameplayAbility::GetAoCActorInfo() const
{
	if (!ensure(CurrentActorInfo))
	{
		return nullptr;
	}
	return static_cast<const FAoCGameplayAbilityActorInfo*>(CurrentActorInfo);
}

UCombatComponent* UAoCGameplayAbility::GetCombatComponentFromActorInfo() const
{
	
	const FAoCGameplayAbilityActorInfo* AoCActorInfo = GetAoCActorInfo();
	return AoCActorInfo ? AoCActorInfo->GetCombatComponent(): nullptr;
}
