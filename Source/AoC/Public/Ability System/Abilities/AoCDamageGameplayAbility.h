// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "AoCDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCDamageGameplayAbility : public UAoCGameplayAbility
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat DamageMagnitude;
};
