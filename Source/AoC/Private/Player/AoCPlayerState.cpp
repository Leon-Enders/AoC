// Created by Leon Enders


#include "Player/AoCPlayerState.h"

#include "AbilitySystemComponent.h"


AAoCPlayerState::AAoCPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAttributeSet>("Attribute Set");
	
}
