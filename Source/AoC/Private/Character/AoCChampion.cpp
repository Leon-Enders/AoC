// Created by Leon Enders


#include "Character/AoCChampion.h"

#include "AbilitySystemComponent.h"
#include "Player/AoCPlayerState.h"

AAoCChampion::AAoCChampion()
{
}

void AAoCChampion::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
	
}

void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
}

