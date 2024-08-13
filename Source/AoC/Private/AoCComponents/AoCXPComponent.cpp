// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCXPComponent.h"
#include "Data/AoCXPDataAsset.h"

UAoCXPComponent::UAoCXPComponent()
{
}

void UAoCXPComponent::InitializeAoCComponent()
{

	
}

void UAoCXPComponent::LogLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Current level is: %i"),Level);
}

void UAoCXPComponent::AddXP(const int32 InXP)
{
	if(UpdateLevel(InXP)) OnLevelChanged.Broadcast(Level);
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

	return bLeveledUp;
}
