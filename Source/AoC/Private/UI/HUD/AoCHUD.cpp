// Created by Leon Enders


#include "UI/HUD/AoCHUD.h"
#include "UI/UserWidget/AocUserWidget.h"
#include "UI/WidgetController/AoCWidgetController.h"


UAoCWidgetController* AAoCHUD::GetWidgetController(APlayerController* PC, APlayerState* PS, UAttributeSet* AS, UAbilitySystemComponent* ASC)
{
	if(WidgetController == nullptr)
	{
		WidgetController = NewObject<UAoCWidgetController>(this, WidgetControllerClass);
		FWidgetControllerParams WidgetControllerParams;
		WidgetControllerParams.PC = PC;
		WidgetControllerParams.PS = PS;
		WidgetControllerParams.AS = AS;
		WidgetControllerParams.ASC = ASC;
	
		WidgetController->InitWidgetController(WidgetControllerParams);
		if(OverlayWidgetClass != nullptr)
		{
		
			OverlayWidget = CreateWidget<UAoCUserWidget>(GetOwningPlayerController(), OverlayWidgetClass);
			OverlayWidget->AddToViewport();
			if(WidgetController != nullptr)
			{
				OverlayWidget->SetWidgetController(WidgetController);
			}
		}
		WidgetController->BroadcastInitialValues();
		return WidgetController;
	}
	return WidgetController;
}

