// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/MeleeComboInfo.h"

float UMeleeComboInfo::GetAttackDistanceForTag(const FGameplayTag& ComboTag)
{
	return DashDistanceDataForTag.FindChecked(ComboTag);
}
