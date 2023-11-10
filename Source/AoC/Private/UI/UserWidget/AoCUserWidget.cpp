// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/UserWidget/AoCUserWidget.h"

void UAoCUserWidget::SetWidgetController(UObject* In_WidgetController)
{
	WidgetController = In_WidgetController;
	WidgetControllerSet();
}

