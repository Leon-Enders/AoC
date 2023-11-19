// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAttributeSet.h"
#include "Net/UnrealNetwork.h"

UAoCAttributeSet::UAoCAttributeSet()
{
	InitHealth(50.f);
	InitHealthMax(100.f);
	InitMana(50.f);
	InitManaMax(100.f);
}

void UAoCAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, HealthMax, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCAttributeSet, ManaMax, COND_None, REPNOTIFY_Always);
}

void UAoCAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if(Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f , GetHealthMax());
	}
	if(Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f , GetManaMax());
	}
	
	
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


