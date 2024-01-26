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

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AAoCProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void SpawnProjectile(const FVector& TargetLocation);

	
};
