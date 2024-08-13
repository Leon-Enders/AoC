// Copyright by Leon Enders ©, All Rights Reserved.


#include "Data/AoCXPDataAsset.h"

FAoCXPData UAoCXPDataAsset::GetXPDataForLevel(const int32 Level) const
{
	return XPDataForLevel.FindChecked(Level);
}
