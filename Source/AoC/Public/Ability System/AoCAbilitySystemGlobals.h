// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemGlobals.h"
#include "AoCAbilitySystemGlobals.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCAbilitySystemGlobals : public UAbilitySystemGlobals
{
	GENERATED_BODY()
public:

	virtual FGameplayEffectContext* AllocGameplayEffectContext() const override;
	virtual FGameplayAbilityActorInfo* AllocAbilityActorInfo() const override;

	template<typename T>
	static T* GetAoCComponentFromSourceObject(const UObject* SourceObject);
};

