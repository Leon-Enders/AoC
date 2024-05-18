// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/CombatComponent.h"
#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}
void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeComboMaps();
	
}

void UCombatComponent::InitializeComboMaps()
{
	// Initialize AttackCount to ComboTags Maps
	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	AttackCountToTagA.Add(0, AoCGameplayTags.Melee_ComboA1);
	AttackCountToTagA.Add(1, AoCGameplayTags.Melee_ComboA2);
	AttackCountToTagA.Add(2, AoCGameplayTags.Melee_ComboA3);
	AttackCountToTagA.Add(3, AoCGameplayTags.Melee_ComboA4);

	AttackCountToTagB.Add(0, AoCGameplayTags.Melee_ComboB1);
	AttackCountToTagB.Add(1, AoCGameplayTags.Melee_ComboB2);
	AttackCountToTagB.Add(2, AoCGameplayTags.Melee_ComboB3);
	AttackCountToTagB.Add(3, AoCGameplayTags.Melee_ComboB4);

	AttackCountToTagC.Add(0, AoCGameplayTags.Melee_ComboC1);
	AttackCountToTagC.Add(1, AoCGameplayTags.Melee_ComboC2);
	AttackCountToTagC.Add(2, AoCGameplayTags.Melee_ComboC3);
	AttackCountToTagC.Add(3, AoCGameplayTags.Melee_ComboC4);

	// Initialize Combo Counter to AttackMap
	ComboToAttackMap.Add(0, AttackCountToTagA);
	ComboToAttackMap.Add(1, AttackCountToTagB);
	ComboToAttackMap.Add(2, AttackCountToTagC);
}
void UCombatComponent::InitCombatComponent(UAbilitySystemComponent* ASC)
{
	if(!ASC) return;;
	AbilitySystemComponent = ASC;

	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	// Initialize GameplayEvent Delegates

	//Bind Lambda to Delegate
	SaveAttackDelegate.BindLambda(
		[this](FGameplayTag GameplayTag,const FGameplayEventData* EventData)
		{
			ComboAttackSave();
		});

	// Add Delegate to event list for specified GameplayTag
	const FGameplayTagContainer SaveAttackTagContainer = FGameplayTagContainer(AoCGameplayTags.Event_Montage_SaveAttack);
	AbilitySystemComponent->AddGameplayEventTagContainerDelegate(SaveAttackTagContainer,SaveAttackDelegate);
	
	ResetAttackDelegate.BindLambda(
		[this](FGameplayTag GameplayTag,const FGameplayEventData* EventData)
		{
			ResetCombo();
		});

	const FGameplayTagContainer ResetTagContainer = FGameplayTagContainer(AoCGameplayTags.Event_Montage_ResetCombo);
	AbilitySystemComponent->AddGameplayEventTagContainerDelegate(ResetTagContainer,ResetAttackDelegate);

	UpdateComboDelegate.BindLambda(
		[this](FGameplayTag GameplayTag,const FGameplayEventData* EventData)
		{
			UpdateCombo();
		});
	const FGameplayTagContainer UpdateComboTagContainer = FGameplayTagContainer(AoCGameplayTags.Event_Montage_NextCombo);
	AbilitySystemComponent->AddGameplayEventTagContainerDelegate(UpdateComboTagContainer,UpdateComboDelegate);
	
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

void UCombatComponent::ActivateCombo()
{
	if(!AbilitySystemComponent) return;
	if(GetOwnerRole()!= ROLE_Authority) return;


	// Get current basic attack combo
	const auto BasicAttackMap = ComboToAttackMap.FindChecked(ComboCount);
	
	// Switch on ComboCount map
	const FGameplayTagContainer GameplayTagContainer= FGameplayTagContainer(BasicAttackMap.FindChecked(AttackCount));
		switch (AttackCount)
		{
		case 0:
			AttackCount = 1;
			break;
		case 1:
			AttackCount = 2;
			break;
		case 2:
			AttackCount = 3;
			break;
		case 3:
			AttackCount = 0;
			break;
		default:;
		}
	if(!AbilitySystemComponent->TryActivateAbilitiesByTag(GameplayTagContainer))
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to activate ability!"));
	}
}

void UCombatComponent::ComboAttackSave()
{
	if(bSaveAttack)
	{
		bSaveAttack = false;
		ActivateCombo();
	}
}

void UCombatComponent::UpdateCombo()
{

	// If we weren't attacking, when dashing, we are not granting the next combo
	if(!bIsAttacking) return;

	// Reset Currently active basic attack
	bIsAttacking = false;
	bSaveAttack = false;
	AttackCount = 0;
	
	switch (ComboCount)
	{
	case 0:
		ComboCount = 1;
		break;
	case 1:
		ComboCount = 2;
		break;
	case 2:
		ComboCount = 0;
		break;
	default:;
	}

	
}

void UCombatComponent::ResetCombo()
{
	bIsAttacking = false;
	bSaveAttack = false;
	AttackCount = 0;
	ComboCount = 0;
}

void UCombatComponent::ClearComboCount()
{
	ComboCount = 0;
}


