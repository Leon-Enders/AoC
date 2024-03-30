// Copyright by Leon Enders ©, All Rights Reserved.


#include "Components/CombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UCombatComponent::StartCombo()
{
	if(bIsAttacking)
	{
		bSaveAttack = true;
	}
	else
	{
		bIsAttacking = true;
		ActivateCombo();
	}
}

void UCombatComponent::InitCombatComponent(UAbilitySystemComponent* ASC)
{
	if(!ASC) return;;
	AbilitySystemComponent = ASC;

	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	// Initialize GameplayEvent Delegates
	const FGameplayTagContainer SaveAttackTagContainer = FGameplayTagContainer(AoCGameplayTags.Event_Montage_SaveAttack);
	SaveAttackDelegate.BindLambda(
		[this](FGameplayTag GameplayTag,const FGameplayEventData* EventData)
		{
			ComboAttackSave();
		});
	AbilitySystemComponent->AddGameplayEventTagContainerDelegate(SaveAttackTagContainer,SaveAttackDelegate);
	
	ResetAttackDelegate.BindLambda(
		[this](FGameplayTag GameplayTag,const FGameplayEventData* EventData)
		{
			ResetCombo();
		});

	const FGameplayTagContainer ResetTagContainer = FGameplayTagContainer(AoCGameplayTags.Event_Montage_Reset);
	AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ResetTagContainer,ResetAttackDelegate);
	
}


void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// Initialize AttackCount to ComboTags Map
	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	AttackCountToTag.Add(0, AoCGameplayTags.Melee_Combo1);
	AttackCountToTag.Add(1, AoCGameplayTags.Melee_Combo2);
	AttackCountToTag.Add(2, AoCGameplayTags.Melee_Combo3);
	
}
void UCombatComponent::ActivateCombo()
{
	if(!AbilitySystemComponent) return;
	// Get the next ComboTag
	const FGameplayTagContainer GameplayTagContainer= FGameplayTagContainer(AttackCountToTag.FindChecked(AttackCount));
	switch (AttackCount)
	{
	case 0:
		AttackCount = 1;
		break;
	case 1:
		AttackCount = 2;
		break;
	case 2:
		AttackCount = 0;
		break;
	default:;
	}
	AbilitySystemComponent->TryActivateAbilitiesByTag(GameplayTagContainer);
}

void UCombatComponent::ComboAttackSave()
{
	if(bSaveAttack)
	{
		bSaveAttack = false;
		ActivateCombo();
	}
}

void UCombatComponent::ResetCombo()
{
	bIsAttacking = false;
	bSaveAttack = false;
	AttackCount = 0;
}


