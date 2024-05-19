// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/AoCSocketManagerInfo.h"

FAoCSocketManagerData UAoCSocketManagerInfo::RetrieveSocketManagerInfo(FName CharacterName)
{
	return SocketManagerDataByName.FindChecked(CharacterName);
}
