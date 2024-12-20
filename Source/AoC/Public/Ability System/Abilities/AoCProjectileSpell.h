// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCDamageGameplayAbility.h"
#include "AoCProjectileSpell.generated.h"

class AAoCProjectile;
/**
 * 
 */
UCLASS()
class AOC_API UAoCProjectileSpell : public UAoCDamageGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	virtual void SpawnProjectile(const FVector& TargetLocation, const bool SpawnOffHand);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAoCProjectile> ProjectileClass;

	UPROPERTY(EditDefaultsOnly)
	bool bIsHomingProjectile = false;
};
