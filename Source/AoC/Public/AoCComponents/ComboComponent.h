// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/ActorComponent.h"
#include "ComboComponent.generated.h"

class UMeleeComboInfo;
//TODO: update for Data-driven design, Rename to AoCComboComponet
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UComboComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UComboComponent();
	void InitCombatComponent(UAbilitySystemComponent* ASC);
	
	UFUNCTION(BlueprintCallable)
	void StartCombo();

	float GetDashDistance(const FGameplayTag& ComboTag)const;
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMeleeComboInfo>MeleeComboInfo;
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

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	bool bIsAttacking = false;
	bool bSaveAttack = false;
	int8 AttackCount = 0;
	int8 ComboCount = 0;
		
};
