// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/AoCAvatarData.h"

FAoCAvatarDataInfo& UAoCAvatarData::RetrieveAvatarDataInfo(const ECharacterClass CharacterClass)
{
	return AvatarDataByClass.FindChecked(CharacterClass);
}
