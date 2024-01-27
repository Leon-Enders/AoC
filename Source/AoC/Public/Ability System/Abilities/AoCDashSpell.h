// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "AoCDashSpell.generated.h"

class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class AOC_API UAoCDashSpell : public UAoCGameplayAbility
{
	GENERATED_BODY()
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable)
	void SpawnParticle(const FVector& TargetLocation);

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> DashEffect;

};
