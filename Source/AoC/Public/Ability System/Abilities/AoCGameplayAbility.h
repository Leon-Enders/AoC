// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AoCGameplayAbility.generated.h"

/**
 * 
 */

UCLASS()
class AOC_API UAoCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	//TODO: Create GetCombatComponentFromActorInfo
};
