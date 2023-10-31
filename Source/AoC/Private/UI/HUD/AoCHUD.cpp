// Created by Leon Enders


#include "UI/HUD/AoCHUD.h"
#include "UI/UserWidget/AocUserWidget.h"

//TODO Widget->SetWidgetController(WidgetController); WidgetController can be set here for the overlaywidget
void AAoCHUD::BeginPlay()
{
	Super::BeginPlay();

	if(OverlayWidgetClass != nullptr)
	{
		
		OverlayWidget = CreateWidget<UAoCUserWidget>(GetOwningPlayerController(), OverlayWidgetClass);
		OverlayWidget->AddToViewport();

		
	}
	
}

