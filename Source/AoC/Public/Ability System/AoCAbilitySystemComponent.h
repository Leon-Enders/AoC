// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AoCAbilitySystemComponent.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectSignature, const FGameplayTagContainer& EffectAssetTags);

UCLASS()
class AOC_API UAoCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	void InitAoCAbilityComponent();

	FEffectSignature EffectDelegate;

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);
	
	void ActivateInputReleased(const FGameplayTag& InputTag);
	void ActivateInputHeld(const FGameplayTag& InputTag);
	
};
