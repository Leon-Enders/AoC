// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCChampion.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoCComponents/AoCComboComponent.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"

AAoCChampion::AAoCChampion()
{
	ComboComponent = CreateDefaultSubobject<UAoCComboComponent>("ComboComponent");
	AoCComponentsMap.Add(UAoCComboComponent::StaticClass(), ComboComponent);
}


void AAoCChampion::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the Server
	InitAbilityActorInfo();
	InitializeAoCComponents();
	
	
	
}
void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
	InitializeAoCComponents();
	
}

void AAoCChampion::InitAbilityActorInfo()
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	//TODO: Create a Delegate on AbilitySystemComponent When AbilityActorInfo is Initialized and bind on playerstate on it initializing pawndata
	PS->InitializePawnData();
	
	if(UAoCAbilitySystemComponent* AoCASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent()))
	{
		AoCASC->InitAoCAbilityComponent();
		
	}
	
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();

	// Make sure to call this after setting AttributeSet
	BindAbilitySystemDelegates();
	
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			AoCHUD->InitOverlay(APC, PS, AbilitySystemComponent, AttributeSet);
		}
	}
	
}

void AAoCChampion::OnAvatarDeath()
{
	Super::OnAvatarDeath();
}

