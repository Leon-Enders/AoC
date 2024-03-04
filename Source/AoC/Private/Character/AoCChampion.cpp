// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCChampion.h"


#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
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
	InitializeAttributes();
	InitializeHealthBar();
	AddCharacterAbilities();
}

void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
	InitializeHealthBar();
	
}

int32 AAoCChampion::GetPlayerLevel()
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}

void AAoCChampion::InitializeAttributes()
{
	Super::InitializeAttributes();
	
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
	
	
	if(APlayerController* APC = Cast<APlayerController>(GetController()))
	{
		if(AAoCHUD* AoCHUD = Cast<AAoCHUD>(APC->GetHUD()))
		{
			AoCHUD->InitOverlay(APC, PS, AbilitySystemComponent, AttributeSet);
		}
		
	}
	
}

FMeleeComboData AAoCChampion::GetMeleeComboInfo_Implementation(const FGameplayTag& ComboTag)
{
	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	FGameplayTagContainer GameplayTagContainer;
	AbilitySystemComponent->GetOwnedGameplayTags(GameplayTagContainer);
	
	for(const auto GameplayTag : GameplayTagContainer)
	{
		
				
				
			
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Abilities_FireMonk_BasicAttack3))
		{
			return MeleeComboInfos[2]->GetMeleeComboInfoByTag(ComboTag);
		}
		if(GameplayTag.MatchesTagExact(AoCGameplayTags.Abilities_FireMonk_BasicAttack2))
		{
			return MeleeComboInfos[1]->GetMeleeComboInfoByTag(ComboTag);
		}
	}
	if(ComboTag.IsValid())
	{
		return MeleeComboInfos[0]->GetMeleeComboInfoByTag(ComboTag);
	}
	
	
	return FMeleeComboData();
}