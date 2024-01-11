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

int32 AAoCChampion::GetPlayerLevel()
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}

void AAoCChampion::InitAbilityActorInfo()
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	UAoCAbilitySystemComponent* AoCASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if(AoCASC)
	{
		AoCASC->InitAoCASC();
	}
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
	
	
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			AoCHUD->InitOverlay(APC, PS, AbilitySystemComponent, AttributeSet);
		}
		
	}

	// Initializes Attributes for this character with GameplayEffects
	InitializeAttributes();
	AddCharacterAbilities();
}

