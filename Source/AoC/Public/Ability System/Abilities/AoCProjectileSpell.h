// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "AoCProjectileSpell.generated.h"

class AAoCProjectile;
/**
 * 
 */
UCLASS()
class AOC_API UAoCProjectileSpell : public UAoCGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

protected:

	UPROPERTY(EditDefaultsOnly, Category="Projetile")
	TSubclassOf<AAoCProjectile> AoCProjectile;

};
