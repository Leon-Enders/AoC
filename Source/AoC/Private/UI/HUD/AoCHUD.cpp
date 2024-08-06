// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/HUD/AoCHUD.h"
#include "UI/UserWidget/AocUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/OverlayWidgetController.h"


UOverlayWidgetController* AAoCHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	if(OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}

	return OverlayWidgetController;
}

UOverlayWidgetController* AAoCHUD::GetOverlayWidgetController() const
{
	if(OverlayWidgetController)return OverlayWidgetController;
	return nullptr;
}

UAttributeMenuWidgetController* AAoCHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if(AttributeMenuWidgetController == nullptr)
	{
		AttributeMenuWidgetController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuWidgetControllerClass);
		AttributeMenuWidgetController->SetWidgetControllerParams(WCParams);
		AttributeMenuWidgetController->BindCallbacksToDependencies();
		return AttributeMenuWidgetController;
	}

	return AttributeMenuWidgetController;
}

void AAoCHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{

	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), TSubclassOf<UAoCUserWidget>(OverlayWidgetClass));
	OverlayWidget = Cast<UAoCUserWidget>(Widget);

	const FWidgetControllerParams WCParams(PC, PS, AS, ASC);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WCParams);
	
	OverlayWidget->SetWidgetController(WidgetController);
	WidgetController->BroadCastInitialValue();
	Widget->AddToViewport();
}

void AAoCHUD::BeginPlay()
{
	Super::BeginPlay();
	
	
}
