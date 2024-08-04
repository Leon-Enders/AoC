// Copyright by Leon Enders ©, All Rights Reserved.


#include "Data/UI/AoCUIAbilityDataAsset.h"

FAoCUIAbilityData UAoCUIAbilityDataAsset::FindAoCUIAbilityDataForTag(const FGameplayTag& AbilityTag,
	bool bLogNotFound) const
{
	for (const auto& Data  : AoCUIAbilitiesData)
	{
		if (Data.AbilityTag == AbilityTag)
		{
			return Data;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find info for AbilityTag [%s] on AbilityInfo [%s]"), *AbilityTag.ToString(), *GetNameSafe(this));
	}

	return FAoCUIAbilityData();
}
