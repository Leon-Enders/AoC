// Copyright by Leon Enders ©, All Rights Reserved.


#include "AsyncTasks/WaitCooldownChange.h"

#include "AbilitySystemComponent.h"

UWaitCooldownChange* UWaitCooldownChange::WaitCooldownChange(UAbilitySystemComponent* InAbilitySystemComponent,
                                                             const FGameplayTag& InCooldownTag)
{
	UWaitCooldownChange* WaitCooldownChange = NewObject<UWaitCooldownChange>();
	WaitCooldownChange->AbilitySystemComponent = InAbilitySystemComponent;
	WaitCooldownChange->CooldownTag = InCooldownTag;
	
	if(!IsValid(InAbilitySystemComponent) || !InCooldownTag.IsValid())
	{
		WaitCooldownChange->EndTask();
		return nullptr;
	}

	

	InAbilitySystemComponent->RegisterGameplayTagEvent(InCooldownTag,EGameplayTagEventType::NewOrRemoved).AddUObject(WaitCooldownChange, &UWaitCooldownChange::CooldownTagChanged);
	InAbilitySystemComponent->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(WaitCooldownChange, &OnActiveEffectAdded);

	return WaitCooldownChange;
	
}

void UWaitCooldownChange::EndTask()
{
	if (!IsValid(AbilitySystemComponent)) return;
	AbilitySystemComponent->RegisterGameplayTagEvent(CooldownTag, EGameplayTagEventType::NewOrRemoved).RemoveAll(this);
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UWaitCooldownChange::CooldownTagChanged(const FGameplayTag InCooldownTag, int32 NewCount)
{
	if (NewCount == 0)
	{
		CooldownEnd.Broadcast(0.f);
	}
}

void UWaitCooldownChange::OnActiveEffectAdded(UAbilitySystemComponent* TargetAbilitySystemComponent, const FGameplayEffectSpec& SpecApplied, FActiveGameplayEffectHandle ActiveEffectHandle)
{

	FGameplayTagContainer AssetTags;
	FGameplayTagContainer GrantedTags;
	
	SpecApplied.GetAllAssetTags(AssetTags);
	SpecApplied.GetAllGrantedTags(GrantedTags);

	
	if(AssetTags.HasTag(CooldownTag) || GrantedTags.HasTag(CooldownTag))
	{
		const FGameplayEffectQuery GameplayEffectQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(CooldownTag.GetSingleTagContainer());
	
		TArray<float> RemainingTimes = AbilitySystemComponent->GetActiveEffectsTimeRemaining(GameplayEffectQuery);

		if(RemainingTimes.Num() > 0)
		{
			float MaxTimeRemaining = RemainingTimes[0];
			for(int32 i = 0; i < RemainingTimes.Num(); i++)
			{
				if(MaxTimeRemaining < RemainingTimes[i])
				{
					MaxTimeRemaining = RemainingTimes[i];
				}
			}
			CooldownStart.Broadcast(MaxTimeRemaining);
		}
	}
}

