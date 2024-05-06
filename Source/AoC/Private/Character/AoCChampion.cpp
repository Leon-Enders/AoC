// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCChampion.h"


#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/Data/MeleeComboInfo.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "AoCComponents/CombatComponent.h"

AAoCChampion::AAoCChampion()
{
}


void AAoCChampion::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	// Init ability actor info for the Server
	InitAbilityActorInfo();
	InitializeAttributes();
	InitializeHealthBar();

	// Initialize Character Abilities and common abilities
	AddCharacterAbilities();
}
void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
	InitializeHealthBar();
	
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
	CombatComponent->InitCombatComponent(AbilitySystemComponent);
	
	
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			AoCHUD->InitOverlay(APC, PS, AbilitySystemComponent, AttributeSet);
		}
		
	}
	
}

void AAoCChampion::AddCharacterAbilities() 
{
	if(!HasAuthority())
	{
		return;
	}
	
	UAoCAbilitySystemComponent* AoCAbilitySystemComponent = CastChecked<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	AoCAbilitySystemComponent->AddCharacterAbilities(StartUpAbilities);
	AoCAbilitySystemComponent->AddCharacterPassiveAbilities(StartUpPassiveAbilities);
}


float AAoCChampion::GetDashDistanceForTag(const FGameplayTag& ComboTag)
{
	return MeleeComboInfo->GetAttackDistanceForTag(ComboTag);
}