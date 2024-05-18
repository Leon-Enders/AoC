// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AoCGameplayAbility.generated.h"

/**
 * 
 */

class UCombatComponent;
struct FAoCGameplayAbilityActorInfo;

UCLASS()
class AOC_API UAoCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	UFUNCTION(BlueprintPure)
	UCombatComponent* GetCombatComponentFromActorInfo() const;
protected:
	
	const FAoCGameplayAbilityActorInfo* GetAoCActorInfo() const;

	
};
