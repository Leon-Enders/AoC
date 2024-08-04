// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AoCAbilitySystemComponent.generated.h"

/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectSignature, const FGameplayTagContainer& EffectAssetTags);
DECLARE_MULTICAST_DELEGATE_OneParam(FAbilitiesGivenSignature, UAoCAbilitySystemComponent*);
DECLARE_DELEGATE_OneParam(FForEachAbilitySignature, const FGameplayAbilitySpec&);

UCLASS()
class AOC_API UAoCAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	void InitAoCAbilityComponent();

	FEffectSignature EffectDelegate;
	FAbilitiesGivenSignature AbilitiesGivenDelegate;

	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& GameplayEffectSpec, FActiveGameplayEffectHandle ActiveGameplayEffectHandle);

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartUpPassiveAbilities);
	
	void ActivateInputReleased(const FGameplayTag& InputTag);
	void ActivateInputHeld(const FGameplayTag& InputTag);


	FGameplayTag GetAbilityTagBySpec(const FGameplayAbilitySpec& AbilitySpec)const;
	FGameplayTag GetInputTagBySpec(const FGameplayAbilitySpec& AbilitySpec)const;
	
	void ExecuteForEachAbility(FForEachAbilitySignature& ForEachAbilityDelegate);
	
	bool bHasStartUpAbilities = false;


protected:
	
	virtual void OnRep_ActivateAbilities() override;
	
};
