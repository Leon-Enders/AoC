// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCXPComponent.h"

#include "Ability System/AoCAttributeSet.h"
#include "Data/AoCXPDataAsset.h"
#include "Net/UnrealNetwork.h"

UAoCXPComponent::UAoCXPComponent()
{
	
}

void UAoCXPComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAoCXPComponent, Level, COND_None, REPNOTIFY_OnChanged);
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCXPComponent, CurrentXP, COND_None, REPNOTIFY_OnChanged);
}

void UAoCXPComponent::SetAttributeSet(UAttributeSet* AoCAttributeSet)
{
	AttributeSet = CastChecked<UAoCAttributeSet>(AoCAttributeSet);
	AttributeSet->OnXPReceivedDelegate.AddUObject(this,&UAoCXPComponent::AddXP);

}



void UAoCXPComponent::LogLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Current level is: %i"),Level);
}

void UAoCXPComponent::AddXP(const int32 InXP)
{
	if(GetOwnerRole() != ROLE_Authority) return;
	
	if(UpdateLevel(InXP)) OnLevelChanged.Broadcast(Level);
	OnXPChanged.Broadcast(CurrentXP);
}


void UAoCXPComponent::SetXP(const int32 InXP)
{
	if(GetOwnerRole() != ROLE_Authority) return;
	
	CurrentXP = InXP;
	OnXPChanged.Broadcast(CurrentXP);
}

void UAoCXPComponent::SetLevel(const int32 InLevel)
{
	if(GetOwnerRole() != ROLE_Authority) return;
	
	Level = InLevel;
	OnLevelChanged.Broadcast(Level);
}

float UAoCXPComponent::GetXPRatio() const
{
	return XPRatio;
}

bool UAoCXPComponent::UpdateLevel(int32 InXP)
{
	bool bLeveledUp = false;
    CurrentXP += InXP;
    
	while(CurrentXP >= XPData->GetXPDataForLevel(Level).LevelUpCost)
	{
		const int32 CurrentLevelUpCost = XPData->GetXPDataForLevel(Level).LevelUpCost;
		CurrentXP -= CurrentLevelUpCost;
		Level++;
		bLeveledUp = true;
	}
	
	const int32 MaxLevel = XPData->MaxLevel;
	
	if(Level >MaxLevel)
	{
		Level = MaxLevel;
	}
	
	return bLeveledUp;
}

void UAoCXPComponent::OnRep_Level()
{
	UE_LOG(LogTemp, Warning, TEXT("Current Level is: %i"),Level);
	OnLevelChanged.Broadcast(Level);
}

void UAoCXPComponent::OnRep_CurrentXP()
{
	UE_LOG(LogTemp, Warning, TEXT("Current XP is: %i"),CurrentXP);
	OnXPChanged.Broadcast(CurrentXP);
}
