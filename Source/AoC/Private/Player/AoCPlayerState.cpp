// Created by Leon Enders


#include "Player/AoCPlayerState.h"

#include "AbilitySystemComponent.h"


AAoCPlayerState::AAoCPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
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
