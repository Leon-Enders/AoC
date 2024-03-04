// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/MeleeComboInfo.h"

FAnimationDataForBasicAttack UMeleeComboInfo::GetAnimationDataForTag(const FGameplayTag& InfoTag)
{
	return AnimationDataForTag.FindChecked(InfoTag);
}
