// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"

void UAoCAbilitySystemComponent::InitAoCAbilityComponent()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAoCAbilitySystemComponent::ClientEffectApplied);
}

void UAoCAbilitySystemComponent::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{

	
	FGameplayTagContainer AssetTags;
	GameplayEffectSpec.GetAllAssetTags(AssetTags);

	EffectDelegate.Broadcast(AssetTags);

}


void UAoCAbilitySystemComponent::ActivateInputReleased(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid())
	{
		return;
	}
	
	for(auto& ActivatableAbility : GetActivatableAbilities())
	{
		if(ActivatableAbility.DynamicAbilityTags.HasTagExact(InputTag))
		{
			ActivatableAbility.InputPressed = false;
		}
	}
}

void UAoCAbilitySystemComponent::ActivateInputHeld(const FGameplayTag& InputTag)
{
	if(!InputTag.IsValid())
	{
		return;
	}
	
	for(auto& ActivatableAbility : GetActivatableAbilities())
	{
		if(ActivatableAbility.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if(!ActivatableAbility.IsActive())
			{
			
				ActivatableAbility.InputPressed = true;
				TryActivateAbility(ActivatableAbility.Handle);
			}
		}
	}
}







