// Copyright by Leon Enders ©, All Rights Reserved.


#include "Data/AoCAbilitySet.h"

#include "ActiveGameplayEffectHandle.h"
#include "GameplayAbilitySpecHandle.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "Data/UI/AoCUIAbilityDataAsset.h"

void FAoCAbilitySet_GrantedHandles::AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle)
{
	if (Handle.IsValid())
	{
		AbilitySpecHandles.Add(Handle);
	}
}

void FAoCAbilitySet_GrantedHandles::AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle)
{
	if (Handle.IsValid())
	{
		GameplayEffectHandles.Add(Handle);
	}
}

void FAoCAbilitySet_GrantedHandles::TakeFromAbilitySystem(UAoCAbilitySystemComponent* AoCASC)
{
	check(AoCASC);

	if (!AoCASC->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		return;
	}

	for (const FGameplayAbilitySpecHandle& Handle : AbilitySpecHandles)
	{
		if (Handle.IsValid())
		{
			AoCASC->ClearAbility(Handle);
		}
	}

	for (const FActiveGameplayEffectHandle& Handle : GameplayEffectHandles)
	{
		if (Handle.IsValid())
		{
			AoCASC->RemoveActiveGameplayEffect(Handle);
		}
	}

	
	AbilitySpecHandles.Reset();
	GameplayEffectHandles.Reset();
}

void UAoCAbilitySet::GiveToAbilitySystem(UAoCAbilitySystemComponent* AoCASC,
                                         FAoCAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject, const float Level) const
{
	
	check(AoCASC);
	if (!AoCASC->IsOwnerActorAuthoritative())
	{
		// Must be authoritative to give or take ability sets.
		return;
	}
	
	// Grant the gameplay abilities.
	for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
	{
		const FAoCAbilitySet_GameplayAbility& AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];

		if (!IsValid(AbilityToGrant.Ability))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayAbilities[%d] on ability set [%s] is not valid."), AbilityIndex, *GetNameSafe(this));
			continue;
		}

		UAoCGameplayAbility* AbilityCDO = AbilityToGrant.Ability->GetDefaultObject<UAoCGameplayAbility>();

		FGameplayAbilitySpec AbilitySpec(AbilityCDO, Level);
		AbilitySpec.SourceObject = SourceObject;
		AbilitySpec.Ability->AbilityTags.AddTag(AbilityToGrant.AbilityTag);
		
		// Only Add InputTag if we have valid AbilityData - this is a workaround to prevent enemies from having InputTags
		if(IsValid(UIAbilityData))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);

			//Initialize the InputTag in Ability Data for each granted ability
			UIAbilityData->SetInputTagForData(AbilityToGrant.AbilityTag, AbilityToGrant.InputTag);
		}
		
		const FGameplayAbilitySpecHandle AbilitySpecHandle = AoCASC->GiveAbility(AbilitySpec);

		
		
		
		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddAbilitySpecHandle(AbilitySpecHandle);
		}
	}

	// Grant the gameplay effects.
	for (int32 EffectIndex = 0; EffectIndex < GrantedGameplayEffects.Num(); ++EffectIndex)
	{
		const FAoCAbilitySet_GameplayEffect& EffectToGrant = GrantedGameplayEffects[EffectIndex];

		if (!IsValid(EffectToGrant.GameplayEffect))
		{
			UE_LOG(LogTemp, Error, TEXT("GrantedGameplayEffects[%d] on ability set [%s] is not valid"), EffectIndex, *GetNameSafe(this));
			continue;
		}

		const UGameplayEffect* GameplayEffect = EffectToGrant.GameplayEffect->GetDefaultObject<UGameplayEffect>();
		const FActiveGameplayEffectHandle GameplayEffectHandle = AoCASC->ApplyGameplayEffectToSelf(GameplayEffect, Level, AoCASC->MakeEffectContext());

		if (OutGrantedHandles)
		{
			OutGrantedHandles->AddGameplayEffectHandle(GameplayEffectHandle);
		}
	}
}
