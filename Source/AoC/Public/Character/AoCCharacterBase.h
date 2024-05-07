// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AoCCharacterBase.generated.h"



class UGameplayAbility;
class UGameplayEffect;
class UAbilitySystemComponent;
class UAttributeSet;
class UWidgetComponent;
struct FOnAttributeChangeData;

UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAoCCharacterBase();

	// Gameplay Ability System
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
	
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	/*Combat Start*/
	UPROPERTY(EditAnywhere, Category="Combat")
	bool bHasWeapon = false;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> AttackComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> OffhandComponent;
	
	UPROPERTY(EditAnywhere, Category="Combat")
	FName AttackSocketName;

	//TODO:: Maybe remove offhand component and simply use Socket Names, Skeletal mesh components only make sense for locations on a seperate mesh



	
	// Handle Character Death for Client and Server
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LifeSpan = 5.f;

	UPROPERTY(EditAnywhere, Category="Animation")
	TObjectPtr<UAnimMontage> HitReactMontage;

	//Combat Interface Overrides
	virtual FVector GetAttackSocketLocation() override;
	virtual FVector GetOffHandSocketLocation() override;
	virtual UAnimMontage* GetHitMontage_Implementation() override;
	virtual void die() override;

	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UCombatComponent> CombatComponent;
	virtual UCombatComponent* GetCombatComponent_Implementation() override;
	
	
	/*TargetSystem*/

	UPROPERTY(EditDefaultsOnly, Category="TargetSystem")
	TObjectPtr<UTargetComponent> TargetComponent;
	virtual UTargetComponent* GetTargetComponent_Implementation() override;
	
	/*TargetSystem End*/
	
	
	/*Combat End*/

	
	// Gameplay Ability System Data
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	// Attribute Setters
	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;

	
	/*Floating Health Bar Start*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
	void InitializeHealthBar();
	
	/*Floating Health Bar End*/

	//Initialize Attributes in child because of different level locations
	virtual void InitializeAttributes() const ;
	
	void ApplyGameplayEffectToSelf(float Level, TSubclassOf<UGameplayEffect> GameplayEffectToApply) const ;

	
};
