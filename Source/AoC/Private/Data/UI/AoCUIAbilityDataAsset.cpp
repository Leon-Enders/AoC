// Copyright by Leon Enders ©, All Rights Reserved.


#include "Data/UI/AoCUIAbilityDataAsset.h"


void UAoCUIAbilityDataAsset::SetInputTagForData( const FGameplayTag& AbilityTag, const FGameplayTag& InputTag)
{
	AbilityTagUIAbilitiesMap.FindChecked(AbilityTag).InputTag = InputTag;
}


