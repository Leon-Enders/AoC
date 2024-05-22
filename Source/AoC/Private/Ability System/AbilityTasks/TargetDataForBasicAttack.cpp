// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataForBasicAttack.h"

#include "AbilitySystemComponent.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "Ability System/AbilityTasks/TargetDataForDash.h"
#include "AoCComponents/ComboComponent.h"
#include "AoCComponents/TargetComponent.h"

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

	AActor* Avatar = Ability->GetAvatarActorFromActorInfo();

	
	bool bIsClose = false;
	const FVector AvatarLocation = Avatar->GetActorLocation();
	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_LocationInfo* TargetData_LocationInfo = new FGameplayAbilityTargetData_LocationInfo();

	const auto AoCAbility = Cast<UAoCGameplayAbility>(Ability);
	if(!AoCAbility)return;
		
	
	

		const FGameplayTag ActivationTag = Ability->AbilityTags.First();
		
	
		const float DashDistance = AoCAbility->GetComboComponentFromInfo()->GetDashDistance(ActivationTag);

		if(const AActor* TargetEnemy = AoCAbility->GetTargetComponentFromInfo()->GetTarget())
		{
			if(FVector::Distance(TargetEnemy->GetActorLocation(), AvatarLocation) < 200.f)
			{
				TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(AvatarLocation);
				bIsClose = true;
			}
		}
	
	
		if(!bIsClose)
		{	
			TargetData_LocationInfo->SourceLocation.LiteralTransform.SetLocation(AvatarLocation);
			TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(AvatarLocation + Avatar->GetActorForwardVector() * DashDistance);
		}
		
		GameplayAbilityTargetDataHandle.Add(TargetData_LocationInfo);
	
		AbilitySystemComponent->ServerSetReplicatedTargetData(
			GetAbilitySpecHandle(),
			GetActivationPredictionKey(),
			GameplayAbilityTargetDataHandle, FGameplayTag(),
					AbilitySystemComponent->ScopedPredictionKey
					);
	
		if(ShouldBroadcastAbilityTaskDelegates())
		{
			ValidData.Broadcast(GameplayAbilityTargetDataHandle);
		}
	
	
	
}


void UTargetDataForBasicAttack::AbilityTargetDataSetCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ClearAbilityReplicatedDataCache(GetAbilitySpecHandle(),Ability->GetCurrentActivationInfo());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
			ValidData.Broadcast(AbilityTargetDataHandle);
		
	}
}

