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

void UAoCAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities)
{
	for(const auto& Ability : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		if(const UAoCGameplayAbility* AoCGameplayAbility = Cast<UAoCGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AoCGameplayAbility->InputTag);
			GiveAbility(AbilitySpec);
		}
	}
	
	bHasStartUpAbilities = true;
	AbilitiesGivenDelegate.Broadcast(this);
}

void UAoCAbilitySystemComponent::AddCharacterPassiveAbilities(
	const TArray<TSubclassOf<UGameplayAbility>>& StartUpPassiveAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartUpPassiveAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		GiveAbility(AbilitySpec);
	}
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

FGameplayTag UAoCAbilitySystemComponent::GetAbilityTagBySpec(const FGameplayAbilitySpec& AbilitySpec) const
{
	for( const FGameplayTag Tag : AbilitySpec.Ability->AbilityTags)
	{
		if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
		{
			return Tag;
		}
	}
	return FGameplayTag();
}

FGameplayTag UAoCAbilitySystemComponent::GetInputTagBySpec(const FGameplayAbilitySpec& AbilitySpec) const
{
	for( const FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if(Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("InputTags"))))
		{
			return Tag;
		}
	}
	
	return FGameplayTag();
}

void UAoCAbilitySystemComponent::ExecuteForEachAbility(FForEachAbilitySignature& ForEachAbilityDelegate)
{
	FScopedAbilityListLock AbilityListLock(*this);

	for(const auto& AbilitySpec : GetActivatableAbilities())
	{
		if(!ForEachAbilityDelegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to execute delegate in %hs"), __FUNCTION__);
		}
	}
}



