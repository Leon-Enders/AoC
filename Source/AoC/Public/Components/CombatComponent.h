// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UCombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	
	UFUNCTION(BlueprintCallable)
	void StartCombo();

	
	void InitCombatComponent(UAbilitySystemComponent* ASC);
protected:

	virtual void BeginPlay() override;
	
private:

	
	void ActivateCombo();
	void ComboAttackSave();
	void ResetCombo();

	// GameplayEventDelegates
	FGameplayEventTagMulticastDelegate::FDelegate SaveAttackDelegate;
	FGameplayEventTagMulticastDelegate::FDelegate ResetAttackDelegate;
	
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	// State Variables
	TMap<int8, FGameplayTag> AttackCountToTag;
	bool bIsAttacking = false;
	bool bSaveAttack = false;
	int8 AttackCount = 0;
		
};
