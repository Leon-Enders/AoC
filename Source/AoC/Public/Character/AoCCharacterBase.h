// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "AoCCharacterBase.generated.h"


class UNiagaraSystem;
class UFloatingBarComponent;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAttributeSet;


UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAoCCharacterBase();

	/*
	 * Getters
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
	
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	
	/*Combat*/

	// Handle Scene Properties
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> MainHandComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> OffhandComponent;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	bool bHasWeapon = false;
	
	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	FName AttackSocketName;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	FName RightHandSocketName;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TArray<FTaggedMontages> TaggedMontages;

	//Combat Interface Overrides
	virtual FVector GetMainHandSocketLocation_Implementation(const FGameplayTag MontageTag) override;
	virtual FVector GetOffHandSocketLocation_Implementation(const FGameplayTag MontageTag) override;
	virtual UAnimMontage* GetHitMontage_Implementation() override;
	virtual TArray<FTaggedMontages> GetTaggedMontages_Implementation() override;
	virtual bool GetIsDead_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual void die() override;

	// Handle Character Death for Client and Server
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();
	

	// Handle Combo
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UCombatComponent> CombatComponent;

	
	/*TargetSystem*/
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UTargetComponent> TargetComponent;
	virtual UTargetComponent* GetTargetComponent_Implementation() override;
	
	/*TargetSystem End*/
	/*Combat End*/
	
	
	// Gameplay Ability System Data
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
	
	// Avatar Properties
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere,Category="AvatarProperties")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AvatarProperties")
	float LifeSpan = 5.f;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UFloatingBarComponent> HealthBarComponent;
	
	virtual void InitializeAttributes() const;

	virtual void InitializeAoCComponents() const;


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* BloodEffect;
private:

	bool bIsDead = false;
};
