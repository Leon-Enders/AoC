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
	DOREPLIFETIME_CONDITION_NOTIFY(UAoCXPComponent, AttributePoints, COND_None, REPNOTIFY_OnChanged);
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
	//Not sure if this is the correct way to check for authority on this component
	if(GetOwnerRole() != ROLE_Authority) return;
	
	if(UpdateLevel(InXP))
	{
		OnAttributePointsChanged.Broadcast(AttributePoints);
		OnLevelChanged.Broadcast(Level);
	}
	OnXPChanged.Broadcast(CurrentXP);
}


void UAoCXPComponent::SetXP(const int32 InXP)
{
	//Not sure if this is the correct way to check for authority on this component
	if(GetOwnerRole() != ROLE_Authority) return;
	
	CurrentXP = InXP;
	OnXPChanged.Broadcast(CurrentXP);
}

void UAoCXPComponent::SetLevel(const int32 InLevel)
{
	//Not sure if this is the correct way to check for authority on this component
	if(GetOwnerRole() != ROLE_Authority) return;
	
	Level = InLevel;
	OnLevelChanged.Broadcast(Level);
}

void UAoCXPComponent::DecreaseAttributePoints()
{
	if(AttributePoints>0)
	{
		AttributePoints--;
	}
	OnAttributePointsChanged.Broadcast(AttributePoints);
}

float UAoCXPComponent::GetXPRatio() const
{
	
	const float CurrentLevelUpCost = XPData->GetXPDataForLevel(Level).LevelUpCost;
	const float CurrentXPF = CurrentXP;
	const float XPRatio = CurrentXPF/CurrentLevelUpCost;
	return XPRatio;
}

bool UAoCXPComponent::UpdateLevel(int32 InXP)
{
	bool bLeveledUp = false;
    CurrentXP += InXP;
	const int32 MaxLevel = XPData->MaxLevel;
	
	while(Level < MaxLevel && CurrentXP >= XPData->GetXPDataForLevel(Level).LevelUpCost)
	{
		const FAoCXPData XPDataForLevel = XPData->GetXPDataForLevel(Level);
		const int32 CurrentLevelUpCost = XPDataForLevel.LevelUpCost;
		CurrentXP -= CurrentLevelUpCost;
		AttributePoints += XPDataForLevel.AttributePointAward;
		Level++;
		bLeveledUp = true;
	}
	
	return bLeveledUp;
}

void UAoCXPComponent::OnRep_Level()
{
	OnLevelChanged.Broadcast(Level);
}

void UAoCXPComponent::OnRep_CurrentXP()
{
	OnXPChanged.Broadcast(CurrentXP);
}

void UAoCXPComponent::OnRep_AttributePoints()
{
	OnAttributePointsChanged.Broadcast(AttributePoints);
}


void UAoCXPComponent::ApplyAttributePoint_Implementation(const FGameplayTag& AttributeTag)
{
	// Decrease AttributePoints
	DecreaseAttributePoints();

	// Find Attribute that got increased
	FGameplayAttribute AttributeToIncrease = AttributeSet->TagsToAttribute.FindChecked(AttributeTag)();

	// Increase Attribute
	AttributeSet->GetOwningAbilitySystemComponentChecked()->ApplyModToAttribute(AttributeToIncrease, EGameplayModOp::Additive, 1.f);
}
