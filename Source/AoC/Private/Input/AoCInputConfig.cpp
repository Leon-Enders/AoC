// Copyright by Leon Enders ©, All Rights Reserved.


#include "Input/AoCInputConfig.h"


const UInputAction* UAoCInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for(const auto& AoCInputAction : AbilityInputActions)
	{
		if(AoCInputAction.InputAction && AoCInputAction.InputTag == InputTag)
		{
			return AoCInputAction.InputAction;
		}
	}

	if(bLogNotFound)
	{
		UE_LOG(LogTemp, Error,TEXT("No Input Action found for: %s, on InputConfig: %s"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
