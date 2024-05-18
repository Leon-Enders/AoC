// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/CombatSystemInterface.h"
#include "AoCCharacterBase.generated.h"


class UNiagaraSystem;
class UFloatingBarComponent;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDieDelegate);
UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatSystemInterface
{
	GENERATED_BODY()

public:
	AAoCCharacterBase();

	/*
	 * Getters
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UCombatComponent* GetCombatComponent()const  override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
	FOnDieDelegate OnDieDelegate;
	
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();


	

	
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UCombatComponent> CombatComponent;
	

	
	// Gameplay Ability System Data
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFloatingBarComponent> HealthBarComponent;
	
	virtual void InitializeAttributes() const;

	virtual void InitializeAoCComponents() const;

	
};
