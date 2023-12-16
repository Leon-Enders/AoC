// Copyright by Leon Enders ©, All Rights Reserved.


#include "Player/AoCPlayerState.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "Net/UnrealNetwork.h"


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

void AAoCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAoCPlayerState, PlayerLevel);
}

void AAoCPlayerState::OnRep_PlayerLevel(int32 OldPlayerLevel)
{
}
