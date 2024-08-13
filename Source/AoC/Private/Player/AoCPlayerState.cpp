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
	DOREPLIFETIME(AAoCPlayerState, PawnData);
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
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr, AbilitySystemComponent->GetAvatarActor(), GetPlayerLevel());
		}
	}
	
	ForceNetUpdate();
}

void AAoCPlayerState::SetPawnData(const UAoCPawnData* InPawnData)
{
	check(InPawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}

	if (PawnData)
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to set PawnData [%s] on player state [%s] that already has valid PawnData [%s]."), *GetNameSafe(InPawnData), *GetNameSafe(this), *GetNameSafe(PawnData));
		return;
	}
	
	PawnData = InPawnData;

	for (const UAoCAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, nullptr);
		}
	}
	
	ForceNetUpdate();
}

void AAoCPlayerState::OnRep_PawnData()
{
	
}


void AAoCPlayerState::OnRep_PlayerLevel(int32 OldPlayerLevel)
{
}
