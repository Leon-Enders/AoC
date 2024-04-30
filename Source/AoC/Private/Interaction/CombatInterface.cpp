// Copyright by Leon Enders ©, All Rights Reserved.


#include "Interaction/CombatInterface.h"

// Add default functionality here for any ICombatInterface functions that are not pure virtual.
int32 ICombatInterface::GetPlayerLevel() const
{
	return 0;
}

FVector ICombatInterface::GetAttackSocketLocation()
{
	return FVector();
}

FVector ICombatInterface::GetOffHandSocketLocation()
{
	return FVector();
}

float ICombatInterface::GetDashDistanceForTag(const FGameplayTag& ComboTag)
{
	return 0;
}
