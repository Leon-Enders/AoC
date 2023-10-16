// Created by Leon Enders


#include "Ability System/AoCAttributeSet.h"
#include "Net/UnrealNetwork.h"

UAoCAttributeSet::UAoCAttributeSet()
{
	InitHealth(500.f);
	InitHealthMax(1000.f);
	InitMana(500.f);
	InitManaMax(500.f);
}

void UAoCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, ManaMax, COND_None, REPNOTIFY_Always);
}

void UAoCAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Health, OldHealth);
	
}

void UAoCAttributeSet::OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, HealthMax, OldHealthMax);
}

void UAoCAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, Mana, OldMana);
}

void UAoCAttributeSet::OnRep_ManaMax(const FGameplayAttributeData& OldManaMax) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAoCAttributeSet, ManaMax, OldManaMax);
}


