// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCEnemyMeleeAttack.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"

void UAoCEnemyMeleeAttack::CauseDamage(AActor* Target)
{

	
	const FGameplayEffectSpecHandle EffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, GetAbilityLevel());


	float DamageValue = DamageMagnitude.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, FAoCGameplayTags::Get().Damage, DamageValue);
	
	if( UAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo())
	{
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(),UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target));
	}
	
	
	
}
