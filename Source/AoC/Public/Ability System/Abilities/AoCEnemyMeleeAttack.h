// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Abilities/AoCDamageGameplayAbility.h"
#include "AoCEnemyMeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCEnemyMeleeAttack : public UAoCDamageGameplayAbility
{
	GENERATED_BODY()

public:

protected:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* Target);
};
