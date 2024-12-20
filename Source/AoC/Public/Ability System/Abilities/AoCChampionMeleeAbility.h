// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Abilities/AoCDamageGameplayAbility.h"
#include "AoCChampionMeleeAbility.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCChampionMeleeAbility : public UAoCDamageGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);

	UFUNCTION(BlueprintImplementableEvent)
	void OnMeleeTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);

	
	FDelegateHandle OnTargetDataReadyCallbackDelegateHandle;
	
};
