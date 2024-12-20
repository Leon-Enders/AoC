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

	template<class UserClass,  typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityInputTag(const UAoCInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc);
	
};

template <class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
void UAoCInputComponent::BindAbilityInputTag(const UAoCInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, HeldFuncType HeldFunc)
{
	check(InputConfig);
	
	for(const auto& AoCInputAction: InputConfig->AbilityInputActions)
	{
		if(AoCInputAction.InputAction && AoCInputAction.InputTag.IsValid())
		{
			if(PressedFunc)
			{
				BindAction(AoCInputAction.InputAction, ETriggerEvent::Started, Object, PressedFunc, AoCInputAction.InputTag);
			}

			if(ReleasedFunc)
			{
				BindAction(AoCInputAction.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, AoCInputAction.InputTag);
			}

			if(HeldFunc)
			{
				BindAction(AoCInputAction.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, AoCInputAction.InputTag);
			}
		}
	}
}
