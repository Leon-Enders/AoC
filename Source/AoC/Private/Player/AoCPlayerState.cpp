// Copyright by Leon Enders ©, All Rights Reserved.


#include "Player/AoCPlayerState.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoCComponents/AoCXPComponent.h"
#include "Data/AoCAbilitySet.h"
#include "Data/AoCPawnData.h"
#include "Net/UnrealNetwork.h"


AAoCPlayerState::AAoCPlayerState()
{
	// ASC and AS Setup
	AbilitySystemComponent = CreateDefaultSubobject<UAoCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UAoCAttributeSet>("Attribute Set");

	XPComponent = CreateDefaultSubobject<UAoCXPComponent>("XP Component");
	XPComponent->OnLevelChanged.AddUObject(this, &AAoCPlayerState::OnPlayerLevelChanged);
	
	NetUpdateFrequency = 100.f;
	
}
UAbilitySystemComponent* AAoCPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
void AAoCPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AAoCPlayerState, PlayerLevel);
}
void AAoCPlayerState::InitializePawnData()
{
	check(PawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	

	for (const UAoCAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, AbilitySystemComponent->GetAvatarActor(), XPComponent->GetLevel());
		}
	}
	
	ForceNetUpdate();
}

void AAoCPlayerState::OnRep_PlayerLevel(int32 OldPlayerLevel)
{
}

void AAoCPlayerState::OnPlayerLevelChanged(int32 NewLevel)
{
	InitializePawnData();
}
