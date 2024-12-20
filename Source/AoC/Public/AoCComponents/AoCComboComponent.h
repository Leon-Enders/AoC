// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponent.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AoCComboComponent.generated.h"


enum class EComboState : uint8;
class UAoCComboDataAsset;

UCLASS( BlueprintType, ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCComboComponent : public UAoCComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAoCComboComponent();
	virtual void InitializeAoCComponent() override;
	
	UFUNCTION(BlueprintCallable)
	void StartCombo();
	float GetDashDistance(const FGameplayTag& ComboTag)const;

private:

	
	void ActivateCombo();
	void ComboAttackSave();
	void UpdateCombo();
	void ResetCombo();
	void ClearComboCount();
	
	// GameplayEventDelegates
	// TODO: These Delegates can be declared in an interface, so that other domains can react on combo events
	FGameplayEventTagMulticastDelegate::FDelegate SaveAttackDelegate;
	FGameplayEventTagMulticastDelegate::FDelegate ResetAttackDelegate;
	FGameplayEventTagMulticastDelegate::FDelegate UpdateComboDelegate;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	bool bIsAttacking = false;
	bool bSaveAttack = false;
	EComboState CurrentComboState;
	uint8 ComboCount = 1;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	TObjectPtr<UAoCComboDataAsset> ComboData;
};
