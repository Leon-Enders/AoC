// Created by Leon Enders


#include "Player/AoCPlayerState.h"

#include "AbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"


AAoCPlayerState::AAoCPlayerState()
{
	// ASC and AS Setup
	AbilitySystemComponent = CreateDefaultSubobject<UAoCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAoCAttributeSet>("Attribute Set");

	NetUpdateFrequency = 100.f;
	
}

UAbilitySystemComponent* AAoCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAoCPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
