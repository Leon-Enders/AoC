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

const UAoCAvatarDataComponent* UAoCGameplayAbility::GetAvatarDataComponentFromInfo()const
{
	const FAoCGameplayAbilityActorInfo* AoCActorInfo = GetAoCActorInfo();
	return AoCActorInfo ? AoCActorInfo->GetAvatarDataComponent(): nullptr;
}

const UAoCSocketManagerComponent* UAoCGameplayAbility::GetSocketManagerComponentFromInfo()const
{
	const FAoCGameplayAbilityActorInfo* AoCActorInfo = GetAoCActorInfo();
	return AoCActorInfo ? AoCActorInfo->GetSocketManagerComponent(): nullptr;
}

const UAoCTargetComponent* UAoCGameplayAbility::GetTargetComponentFromInfo()const
{
	const FAoCGameplayAbilityActorInfo* AoCActorInfo = GetAoCActorInfo();
	return AoCActorInfo ? AoCActorInfo->GetTargetComponent(): nullptr;
}

const UAoCComboComponent* UAoCGameplayAbility::GetComboComponentFromInfo()const
{
	const FAoCGameplayAbilityActorInfo* AoCActorInfo = GetAoCActorInfo();
	return AoCActorInfo ? AoCActorInfo->GetComboComponent(): nullptr;
}
