// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "Ability System/Data/AttributeInfo.h"

#include "Ability System/AoCAttributeSet.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	Super::BindCallbacksToDependencies();
	
}

void UAttributeMenuWidgetController::BroadCastInitialValue()
{
	check(AttributeInfos);
	
	UAoCAttributeSet* AoCAS = CastChecked<UAoCAttributeSet>(AttributeSet);

	for(auto& pair : AoCAS->TagsToAttribute)
	{
		FAoCAttributeInfo Info = AttributeInfos->FindAttributeInfoByTag(pair.Key);
		Info.AttributeValue = pair.Value().GetNumericValue(AttributeSet);
		AttributeInfoDelegate.Broadcast(Info);
	}
	
}
