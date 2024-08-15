// Copyright by Leon Enders ©, All Rights Reserved.


#include "Player/AoCPlayerState.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoCComponents/AoCXPComponent.h"
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
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &AbilitySetHandles.AddDefaulted_GetRef(), AbilitySystemComponent->GetAvatarActor(), XPComponent->GetLevel());
		}
	}
	
	ForceNetUpdate();
}

void AAoCPlayerState::UpdateAbilitySet()
{
	check(PawnData);

	if (GetLocalRole() != ROLE_Authority)
	{
		return;
	}
	
	// Remove Old granted Abilities/Effects
	for (FAoCAbilitySet_GrantedHandles& SetHandle : AbilitySetHandles)
	{
		SetHandle.TakeFromAbilitySystem(AbilitySystemComponent);
	}
	
	// Give New ones
	for (const UAoCAbilitySet* AbilitySet : PawnData->AbilitySets)
	{
		if (AbilitySet)
		{
			AbilitySet->GiveToAbilitySystem(AbilitySystemComponent, &AbilitySetHandles.AddDefaulted_GetRef(), AbilitySystemComponent->GetAvatarActor(), XPComponent->GetLevel());
		}
	}
	
	ForceNetUpdate();
}

void AAoCPlayerState::OnPlayerLevelChanged(int32 NewLevel)
{
	UpdateAbilitySet();
}
