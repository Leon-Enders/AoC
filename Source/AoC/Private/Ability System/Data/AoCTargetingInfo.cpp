// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/AoCTargetingInfo.h"

FAoCTargetingData UAoCTargetingInfo::RetrieveAoCTargetingData(const FName& CharacterName)
{
	return TagToAoCTargetingData.FindChecked(CharacterName);
}
