// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCComboComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"
#include "Data/AoCComboDataAsset.h"


UAoCComboComponent::UAoCComboComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentComboState = EComboState::CS_A;
	
}

void UAoCComboComponent::InitializeAoCComponent()
{
	if(UAbilitySystemComponent* OwnerAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner()))
	{
		AbilitySystemComponent = OwnerAbilitySystemComponent;
	}

	
	
	
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



void UAoCComboComponent::StartCombo()
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

float UAoCComboComponent::GetDashDistance(const FGameplayTag& ComboTag)const
{
	//TODO: Correctly return by tag
	return 0.f;
}



void UAoCComboComponent::ActivateCombo()
{
	if(!AbilitySystemComponent) return;
	if(GetOwnerRole()!= ROLE_Authority) return;


	// Get current basic attack combo
	const auto currentComboStatesMap = ComboData->Combos.FindChecked(ComboCount);
	
	// Switch on ComboCount map
	const FGameplayTagContainer GameplayTagContainer= FGameplayTagContainer(currentComboStatesMap.ComboStateToGameplayTagMap.FindChecked(CurrentComboState));
		switch (CurrentComboState)
		{
		case EComboState::CS_A:
			CurrentComboState = EComboState::CS_B;
			break;
		case EComboState::CS_B:
			CurrentComboState = EComboState::CS_C;
			break;
		case EComboState::CS_C:
			CurrentComboState = EComboState::CS_D;
			break;
		case EComboState::CS_D:
			CurrentComboState = EComboState::CS_A;
			break;
		default:;
		}
	if(!AbilitySystemComponent->TryActivateAbilitiesByTag(GameplayTagContainer))
	{
		ResetCombo();
	}
	
}

void UAoCComboComponent::ComboAttackSave()
{
	if(bSaveAttack)
	{
		bSaveAttack = false;
		ActivateCombo();
	}
}

void UAoCComboComponent::UpdateCombo()
{

	// If we weren't attacking, when dashing, we are not granting the next combo
	if(!bIsAttacking) return;

	// Reset Currently active basic attack
	bIsAttacking = false;
	bSaveAttack = false;
	CurrentComboState = EComboState::CS_A;
	
	switch (ComboCount)
	{
	case 1:
		ComboCount = 2;
		break;
	case 2:
		ComboCount = 3;
		break;
	case 3:
		ComboCount = 1;
		break;
	default:;
	}

	
}

void UAoCComboComponent::ResetCombo()
{
	bIsAttacking = false;
	bSaveAttack = false;
	CurrentComboState = EComboState::CS_A;
	ComboCount = 1;
}


void UAoCComboComponent::ClearComboCount()
{
	ComboCount = 1;
}