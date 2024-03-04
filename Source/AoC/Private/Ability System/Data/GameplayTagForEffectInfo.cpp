// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/GameplayTagForEffectInfo.h"

TSubclassOf<UGameplayEffect>& UGameplayTagForEffectInfo::GetEffectByTag(const FGameplayTag& InfoTag)
{
	return GameplayEffectForTag.FindChecked(InfoTag);
}
