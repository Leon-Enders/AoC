// Copyright by Leon Enders ©, All Rights Reserved.


#include "Data/AoCChampionAbilitySet.h"

#include "GameplayAbilitySpec.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "Data/UI/AoCUIAbilityDataAsset.h"

void UAoCChampionAbilitySet::GiveToAbilitySystem(UAoCAbilitySystemComponent* AoCASC,
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
		AbilitySpec.DynamicAbilityTags.AddTag(AbilityToGrant.InputTag);
		const FGameplayAbilitySpecHandle AbilitySpecHandle = AoCASC->GiveAbility(AbilitySpec);

		//Initialize the InputTag in Ability Data for each granted ability
		UIAbilityData->SetInputTagForData(AbilityToGrant.AbilityTag, AbilityToGrant.InputTag);
		
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
