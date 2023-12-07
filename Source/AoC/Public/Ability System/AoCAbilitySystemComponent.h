// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AoCAbilitySystemComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameplayTagsAppliedSignature, const FGameplayEffectSpec&, GameplayEffectSpec);

UCLASS()
class AOC_API UAoCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void InitAoCASC();
	

	FGameplayTagsAppliedSignature GameplayTagsAppliedDelegate;
	
	void GameplayEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
};
