// Copyright by Leon Enders ©, All Rights Reserved.


#include "Data/UI/AoCUIAbilityDataAsset.h"

FAoCUIAbilityData UAoCUIAbilityDataAsset::GetAoCUIAbilityDataByTag(const FGameplayTag& InputTag)
{
	for(const auto& Data : AoCUIAbilitiesData)
	{
		if(Data.InputTag.MatchesTagExact(InputTag))
		{
			return Data;
		}
	}

	return FAoCUIAbilityData();
}