// Created by Leon Enders


#include "Ability System/AoCAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAoCAttributeSet::UAoCAttributeSet()
{
	
}

void UAoCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, ManaMax, COND_None, REPNOTIFY_Always);
}

void UAoCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Health, OldHealth);
	
}

void UAoCAttributeSet::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, HealthMax, OldHealthMax);
}

void UAoCAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Mana, OldMana);
}

void UAoCAttributeSet::OnRep_ManaMax(const FGameplayAttributeData& OldManaMax)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, ManaMax, OldManaMax);
}


