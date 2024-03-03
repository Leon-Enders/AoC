// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataForBasicAttack.h"

#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"
#include "Ability System/AbilityTasks/TargetDataForDash.h"

UTargetDataForBasicAttack* UTargetDataForBasicAttack::CreateTargetDataForDash(UGameplayAbility* OwningAbility)
{
	UTargetDataForBasicAttack* myObj = NewAbilityTask<UTargetDataForBasicAttack>(OwningAbility);
	return myObj;
}



void UTargetDataForBasicAttack::Activate()
{
	Super::Activate();

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendBasicAttackTargetData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataForBasicAttack::AbilityTargetDataSetCallback);
		AbilitySystemComponent->CallAllReplicatedDelegatesIfSet(AbilitySpecHandle,ActivationPredictionKey);
	}
}



void UTargetDataForBasicAttack::SendBasicAttackTargetData()
{
	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());

	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	FGameplayTagContainer GameplayTagContainer;
	AbilitySystemComponent->GetOwnedGameplayTags(GameplayTagContainer);
	CurrentComboTag = AoCGameplayTags.Melee_Combo1;
	for(const auto GameplayTag : GameplayTagContainer)
	{
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Melee_Combo1))
		{
			
			break;
		}
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Melee_Combo2))
		{
			CurrentComboTag = AoCGameplayTags.Melee_Combo2;
			break;
		}
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Melee_Combo3))
		{
			CurrentComboTag = AoCGameplayTags.Melee_Combo3;
			break;
		}
	}
	
	// ServerSetReplicatedTargetDataCancelled to cancel data
	
		FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
		FGameplayAbilityTargetData_LocationInfo* TargetData_LocationInfo = new FGameplayAbilityTargetData_LocationInfo();

		TargetData_LocationInfo->SourceLocation.LiteralTransform.SetLocation(GetAvatarActor()->GetActorLocation());
		TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(GetAvatarActor()->GetActorForwardVector());
		GameplayAbilityTargetDataHandle.Add(TargetData_LocationInfo);
	
		AbilitySystemComponent->ServerSetReplicatedTargetData(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			GameplayAbilityTargetDataHandle, CurrentComboTag,
					AbilitySystemComponent->ScopedPredictionKey
					);
	
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(GameplayAbilityTargetDataHandle, CurrentComboTag);
		}
	
	
	
}


void UTargetDataForBasicAttack::AbilityTargetDataSetCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ClearAbilityReplicatedDataCache(GetAbilitySpecHandle(),Ability->GetCurrentActivationInfo());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		
			ValidData.Broadcast(AbilityTargetDataHandle, ActivationTag);
		
		
	}
}

