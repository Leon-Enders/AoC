// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Data/AoCComboInfo.h"



FAoCComboData UAoCComboInfo::RetrieveComboDataByName(const FName& CharacterName)
{
	return ComboDataByName.FindChecked(CharacterName);
}
