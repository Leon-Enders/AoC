// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/AoCWidgetController.h"

void UAoCWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PC;
	PlayerState = WCParams.PS;
	AbilitySystemComponent = WCParams.ASC;
	AttributeSet = WCParams.AS;
}

void UAoCWidgetController::BroadCastInitialValue()
{
	
}

void UAoCWidgetController::BindCallbacksToDependencies()
{
	
}


