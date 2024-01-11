// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemComponent.h"

#include "Ability System/Abilities/AoCGameplayAbility.h"

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

void UAoCAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities)
{
	for(const auto& Ability : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		const UAoCGameplayAbility* AoCGameplayAbility = Cast<UAoCGameplayAbility>(AbilitySpec.Ability);
		AbilitySpec.DynamicAbilityTags.AddTag(AoCGameplayAbility->InputTag);
		GiveAbility(AbilitySpec);
	}
}

void UAoCAbilitySystemComponent::ActivateInputPressed(const FGameplayTag& InputTag)
{
	
	
}

void UAoCAbilitySystemComponent::ActivateInputReleased(const FGameplayTag& InputTag)
{
	for(auto& GameplayAbilitySpec:GetActivatableAbilities())
	{
		if(GameplayAbilitySpec.IsActive())
		{
			if(GameplayAbilitySpec.DynamicAbilityTags.HasTag(InputTag))
			{
				GameplayAbilitySpec.InputPressed = false;
			}
		}
	}
}

void UAoCAbilitySystemComponent::ActivateInputHeld(const FGameplayTag& InputTag)
{
	for(auto& GameplayAbilitySpec:GetActivatableAbilities())
	{
		if(!GameplayAbilitySpec.IsActive())
		{
			if(GameplayAbilitySpec.DynamicAbilityTags.HasTag(InputTag))
			{
				GameplayAbilitySpec.InputPressed = true;
				TryActivateAbility(GameplayAbilitySpec.Handle);
			}
		}
	}
}


