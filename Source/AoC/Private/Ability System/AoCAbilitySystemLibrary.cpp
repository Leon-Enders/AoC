// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemLibrary.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "UI/WidgetController/AoCWidgetController.h"

UAttributeMenuWidgetController* UAoCAbilitySystemLibrary::GetAttributeMenuWidgetController(UObject* WorldContextObject)
{
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AAoCHUD* HUD = Cast<AAoCHUD>(PC->GetHUD()))
		{
			AAoCPlayerState* PS = PC->GetPlayerState<AAoCPlayerState>();
			UAoCAbilitySystemComponent* ASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAoCAttributeSet* AS = Cast<UAoCAttributeSet>(PS->GetAttributeSet());

			
			const FWidgetControllerParams WidgetControllerParams(PC, PS, AS, ASC);
			return HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
		
		
	}
	
	return nullptr;
}

UOverlayWidgetController* UAoCAbilitySystemLibrary::GetOverlayWidgetController(UObject* WorldContextObject)
{
	
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AAoCHUD* HUD = Cast<AAoCHUD>(PC->GetHUD()))
		{
			AAoCPlayerState* PS = PC->GetPlayerState<AAoCPlayerState>();
			UAoCAbilitySystemComponent* ASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAoCAttributeSet* AS = Cast<UAoCAttributeSet>(PS->GetAttributeSet());

			
			const FWidgetControllerParams WidgetControllerParams(PC, PS, AS, ASC);
			return HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
		
		
	}
	
	return nullptr;
}
