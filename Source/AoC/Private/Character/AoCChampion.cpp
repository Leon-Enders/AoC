// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCChampion.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
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
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	PS->InitializePawnData();
	InitAbilityActorInfo();
	InitializeAoCComponents();
	UAoCAbilitySystemComponent* AoCASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	check(AoCASC);
	AoCASC->bHasStartUpAbilities = true;
	AoCASC->AbilitiesGivenDelegate.Broadcast(AoCASC);
	
	
	
}
void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
	InitializeAoCComponents();
	
}

int32 AAoCChampion::GetPlayerLevel() const
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}

void AAoCChampion::InitializeAttributes() const
{
	
	UAoCAbilitySystemLibrary::InitializeAttributes(this, CharacterClass, GetPlayerLevel(),AbilitySystemComponent);

}

void AAoCChampion::InitAbilityActorInfo()
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	UAoCAbilitySystemComponent* AoCASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if(AoCASC)
	{
		AoCASC->InitAoCAbilityComponent();
	}
	
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
	AttributeSet = PS->GetAttributeSet();
	
	// This will initialize the ability set of the current player granting abilities + attribute effects
	
	
	
	
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			// Initialize
			
			AoCHUD->InitOverlay(APC, PS, AbilitySystemComponent, AttributeSet);
		}
	}
	
}


void AAoCChampion::AddCharacterAbilities()const
{
	if(!HasAuthority())
	{
		return;
	}
	
	UAoCAbilitySystemComponent* AoCAbilitySystemComponent = CastChecked<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	AoCAbilitySystemComponent->AddCharacterAbilities(StartUpAbilities);
	AoCAbilitySystemComponent->AddCharacterPassiveAbilities(StartUpPassiveAbilities);
}

