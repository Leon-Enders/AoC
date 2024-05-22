// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCChampion.h"


#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/AoCAttributeSet.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "AoCComponents/ComboComponent.h"

AAoCChampion::AAoCChampion()
{
	AoCComponentsMap.Add(EAoCComponents::ComboComponent, Cast<IAoCComponentInterface>(CreateDefaultSubobject<UComboComponent>("ComboComponent")));
}


void AAoCChampion::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the Server
	InitAbilityActorInfo();
	InitializeAttributes();
	InitializeAoCComponents();

	// Initialize Character Abilities and common abilities
	AddCharacterAbilities();
}
void AAoCChampion::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
	InitializeAoCComponents();
	
}

int32 AAoCChampion::GetPlayerLevel_Implementation() const
{
	AAoCPlayerState* PS = GetPlayerState<AAoCPlayerState>();
	check(PS);
	return PS->GetPlayerLevel();
}

void AAoCChampion::InitializeAttributes() const
{
	
	UAoCAbilitySystemLibrary::InitializeAttributes(this, CharacterClass, IAoCAvatarDataInterface::Execute_GetPlayerLevel(this),AbilitySystemComponent);

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

float AAoCChampion::GetDashDistance_Implementation(const FGameplayTag& ComboTag)
{
	UComboComponent* ComboComponent = Cast<UComboComponent>(AoCComponentsMap[EAoCComponents::ComboComponent]);
	return ComboComponent->GetDashDistance(ComboTag);
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



void AAoCChampion::InitializeAoCComponents() const
{
	Super::InitializeAoCComponents();
}
