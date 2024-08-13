// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCXPComponent.h"
#include "Data/AoCXPDataAsset.h"

UAoCXPComponent::UAoCXPComponent()
{
}

void UAoCXPComponent::InitializeAoCComponent()
{

	
}

void UAoCXPComponent::AddXP(const int32 InXP)
{
	CurrentXP += InXP;
	OnXPChanged.Broadcast(CurrentXP);
}


void UAoCXPComponent::SetXP(const int32 InXP)
{
	CurrentXP = InXP;
	OnXPChanged.Broadcast(CurrentXP);
}

void UAoCXPComponent::SetLevel(const int32 InLevel)
{
	Level = InLevel;
	OnLevelChanged.Broadcast(Level);
}

float UAoCXPComponent::GetXPRatio() const
{
	return XPRatio;
}

void UAoCXPComponent::UpdateLevel(int32 InXP)
{
	const int32 CurrentLevelUpCost = XPData->GetXPDataForLevel(Level).LevelUpCost;
	CurrentXP += InXP;
	
	if(CurrentXP >= CurrentLevelUpCost)
	{
		CurrentXP-=CurrentLevelUpCost;
		Level++;
		UpdateLevel(CurrentXP);
	}
}
