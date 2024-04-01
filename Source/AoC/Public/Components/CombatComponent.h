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

	void InitializeComboMaps();
	void ActivateCombo();
	void ComboAttackSave();
	void UpdateCombo();
	void ResetCombo();
	void ClearComboCount();
	

	
	// GameplayEventDelegates
	FGameplayEventTagMulticastDelegate::FDelegate SaveAttackDelegate;
	FGameplayEventTagMulticastDelegate::FDelegate ResetAttackDelegate;
	FGameplayEventTagMulticastDelegate::FDelegate UpdateComboDelegate;

	// TimerHandle to reset Combo count
	FTimerHandle ComboResetTimerHandle;
	
	// Behaviour Variables

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	float ComboTime = 2.f;

	// State Variables

	// Create a map for each AttackCombo
	TMap<int8, FGameplayTag> AttackCountToTagA;
	TMap<int8, FGameplayTag> AttackCountToTagB;
	TMap<int8, FGameplayTag> AttackCountToTagC;

	// Create a map, mapping Combo index to AttackCombo map
	TMap<int8, TMap<int8, FGameplayTag>> ComboToAttackMap;


	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	bool bIsAttacking = false;
	bool bSaveAttack = false;
	int8 AttackCount = 0;
	int8 ComboCount = 0;
		
};
