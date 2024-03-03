// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/MeleeComboInfo.h"

FMeleeComboData UMeleeComboInfo::GetMeleeComboInfoByTag(const FGameplayTag& InfoTag)
{
	return MeleeComboInfoForTag.FindChecked(InfoTag);
}
