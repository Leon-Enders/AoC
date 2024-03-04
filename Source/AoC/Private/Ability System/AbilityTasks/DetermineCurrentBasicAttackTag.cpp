// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/DetermineCurrentBasicAttackTag.h"

#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"

UDetermineCurrentBasicAttackTag* UDetermineCurrentBasicAttackTag::CreateValidTagData(UGameplayAbility* OwningAbility)
{
	UDetermineCurrentBasicAttackTag* myObj = NewAbilityTask<UDetermineCurrentBasicAttackTag>(OwningAbility);
	return myObj;
}


void UDetermineCurrentBasicAttackTag::Activate()
{
	Super::Activate();

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendValidTagData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(this, &UDetermineCurrentBasicAttackTag::AbilityTargetDataSetCallback);
		AbilitySystemComponent->CallAllReplicatedDelegatesIfSet(AbilitySpecHandle,ActivationPredictionKey);
	}
	
}



void UDetermineCurrentBasicAttackTag::SendValidTagData()
{
	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());

	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	FGameplayTagContainer GameplayTagContainer;
	AbilitySystemComponent->GetOwnedGameplayTags(GameplayTagContainer);
	CurrentBasicAttackTag = AoCGameplayTags.Abilities_FireMonk_BasicAttack1;
	for(const auto GameplayTag : GameplayTagContainer)
	{
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Abilities_FireMonk_BasicAttack1))
		{
			
			break;
		}
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Abilities_FireMonk_BasicAttack2))
		{
			CurrentBasicAttackTag = AoCGameplayTags.Abilities_FireMonk_BasicAttack2;
			break;
		}
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Abilities_FireMonk_BasicAttack3))
		{
			CurrentBasicAttackTag = AoCGameplayTags.Abilities_FireMonk_BasicAttack3;
			break;
		}
	}
	
	// ServerSetReplicatedTargetDataCancelled to cancel data
	
	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		GameplayAbilityTargetDataHandle, CurrentBasicAttackTag,
				AbilitySystemComponent->ScopedPredictionKey
				);
	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidTag.Broadcast(CurrentBasicAttackTag);
	}
}


void UDetermineCurrentBasicAttackTag::AbilityTargetDataSetCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ClearAbilityReplicatedDataCache(GetAbilitySpecHandle(),Ability->GetCurrentActivationInfo());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		
		ValidTag.Broadcast(ActivationTag);
		
		
	}
}
