// Created by Leon Enders


#include "UI/UserWidget/AoCUserWidget.h"
#include "UI/WidgetController/AoCWidgetController.h"


void UAoCUserWidget::SetWidgetController(UAoCWidgetController* In_WidgetController)
{
	check(In_WidgetController);
	WidgetController = In_WidgetController;
	WidgetControllerSet();
}
