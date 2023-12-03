// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCChampion.h"


#include "Ability System/AoCAbilitySystemComponent.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"

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


	UAoCAbilitySystemComponent* AoCASC = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	if(AoCASC)
	{
		AoCASC->InitAoCASC();
	}
	
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			AoCHUD->InitOverlay(APC, PS, AbilitySystemComponent, AttributeSet);
		}
		
	}
}

