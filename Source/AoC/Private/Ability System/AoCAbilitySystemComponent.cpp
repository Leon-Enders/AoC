// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemComponent.h"

void UAoCAbilitySystemComponent::InitAoCASC()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAoCAbilitySystemComponent::EffectApplied);
}

void UAoCAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{

	
	FGameplayTagContainer AssetTags;
	GameplayEffectSpec.GetAllAssetTags(AssetTags);

	EffectDelegate.Broadcast(AssetTags);

}


