// Created by Leon Enders


#include "Character/AoCChampion.h"

#include "AbilitySystemComponent.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "UI/WidgetController/AoCWidgetController.h"

AAoCChampion::AAoCChampion()
{
}

void AAoCChampion::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	// Init ability actor info for the Server
	InitAbilityActorInfo();
	
}

void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

void AAoCChampion::InitAbilityActorInfo()
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);

	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
//TODO: Debug time brotha. check params durch
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			if(UAoCWidgetController* WidgetController = AoCHUD->GetWidgetController
			(APC, GetPlayerState(), AttributeSet, AbilitySystemComponent))
			{
				
			}
		}
		
	}
}

