// Created by Leon Enders


#include "UI/UserWidget/AoCUserWidget.h"

void UAoCUserWidget::SetWidgetController(UObject* In_WidgetController)
{
	WidgetController = In_WidgetController;
	WidgetControllerSet();
}

