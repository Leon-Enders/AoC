// Created by Leon Enders


#include "Player/AoCPlayerState.h"

#include "AbilitySystemComponent.h"


AAoCPlayerState::AAoCPlayerState()
{
	NetUpdateFrequency = 100.f;
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("Attribute Set");
	
}

UAbilitySystemComponent* AAoCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAoCPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
