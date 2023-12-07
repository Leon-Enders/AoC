// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemComponent.h"

void UAoCAbilitySystemComponent::InitAoCASC()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UAoCAbilitySystemComponent::GameplayEffectApplied);
}

void UAoCAbilitySystemComponent::GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle)
{

	GameplayTagsAppliedDelegate.Broadcast(GameplayEffectSpec);
//	FGameplayTagContainer ActiveTags;
//	GameplayEffectSpec.GetAllGrantedTags(ActiveTags);
//
//	for(auto Tag : ActiveTags)
//	{
//
//		FString DisplayText = FString::Printf(TEXT("GameplayTag applied: "));
//		FString Display = DisplayText + Tag.ToString();
//		
//		if(GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, Display);
//		}
//	}
//
}


