// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "UI/WidgetController/AoCWidgetController.h"

UAttributeMenuWidgetController* UAoCAbilitySystemLibrary::GetAttributeMenuWidgetController(UObject* WorldContextObject)
{
	check(WorldContextObject);
	APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController();
	AAoCPlayerState* PS = PC->GetPlayerState<AAoCPlayerState>();
	
	FWidgetControllerParams WidgetControllerParams;
	WidgetControllerParams.PC = PC;
	WidgetControllerParams.PS = PS;
	WidgetControllerParams.AS = PS->GetAttributeSet();
	WidgetControllerParams.ASC = PS->GetAbilitySystemComponent();
	
	if(AAoCHUD* HUD = Cast<AAoCHUD>(PC->GetHUD()))
	{
		return HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
	}

	
	return nullptr;
}

UOverlayWidgetController* UAoCAbilitySystemLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{
	check(WorldContextObject);
	APlayerController* PC = WorldContextObject->GetWorld()->GetFirstPlayerController();
	AAoCPlayerState* PS = PC->GetPlayerState<AAoCPlayerState>();
	
	FWidgetControllerParams WidgetControllerParams;
	WidgetControllerParams.PC = PC;
	WidgetControllerParams.PS = PS;
	WidgetControllerParams.AS = PS->GetAttributeSet();
	WidgetControllerParams.ASC = PS->GetAbilitySystemComponent();
	
	if(AAoCHUD* HUD = Cast<AAoCHUD>(PC->GetHUD()))
	{
		return HUD->GetOverlayWidgetController(WidgetControllerParams);
	}

	
	return nullptr;
}
