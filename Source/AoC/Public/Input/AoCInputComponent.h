// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCInputConfig.h"
#include "EnhancedInputComponent.h"
#include "AoCInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:

	template<class UserObject,  typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityInputTag(UAoCInputConfig* InputConfig, UserObject User, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserObject, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAoCInputComponent::BindAbilityInputTag(UAoCInputConfig* InputConfig, UserObject User, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{

	for(const auto& AoCInputAction: InputConfig->AbilityInputActions)
	{
		if(PressedFunc)
		{
			BindAction(AoCInputAction.InputAction, ETriggerEvent::Started, User, PressedFunc, AoCInputAction.InputTag);
		}

		if(ReleasedFunc)
		{
			BindAction(AoCInputAction.InputAction, ETriggerEvent::Completed, User, ReleasedFunc, AoCInputAction.InputTag);
		}

		if(HeldFunc)
		{
			BindAction(AoCInputAction.InputAction, ETriggerEvent::Triggered, User, HeldFunc, AoCInputAction.InputTag);
		}
	}
}
