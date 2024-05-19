// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/AoCAvatarDataInfo.h"

FAoCAvatarData UAoCAvatarDataInfo::RetrieveAvatarDataInfo(FName CharacterName)
{
	return AvatarDataByName.FindChecked(CharacterName);
}
