// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/AoCAvatarDataInterface.h"
#include "Interaction/CombatInterface.h"
#include "AoCCharacterBase.generated.h"


class UAoCAvatarDataComponent;
class UComboComponent;
class UNiagaraSystem;
class UFloatingBarComponent;
class UGameplayAbility;
class UAbilitySystemComponent;
class UAttributeSet;



UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public IAoCAvatarDataInterface, public ICombatInterface
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
	
	//Combat Interface Overrides
	virtual FVector GetMainHandSocketLocation_Implementation(const FGameplayTag MontageTag) override;
	virtual FVector GetOffHandSocketLocation_Implementation(const FGameplayTag MontageTag) override;
	virtual bool GetIsDead_Implementation() override;
	virtual void die() override;

	// Handle Character Death for Client and Server
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();
	
	// Handle Combo
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UComboComponent> ComboComponent;

	/*TargetSystem*/
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UTargetComponent> TargetComponent;
	virtual UTargetComponent* GetTargetComponent_Implementation() override;
	
	/*TargetSystem End*/
	/*Combat End*/
	
	
	

	// Avatar Properties
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	FName CharacterName;
	
	UPROPERTY(VisibleDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UAoCAvatarDataComponent> AvatarDataComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;
	
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UFloatingBarComponent> HealthBarComponent;


	//~IAoCAvatarDataInterface interface
	virtual UAnimMontage* GetHitMontage_Implementation() override;
	virtual UAnimMontage* GetDeathMontage_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual TArray<FGameplayTagMontage> GetGameplayMontages_Implementation() override;
	//~End of IAoCAvatarDataInterface interface
	
	


	// GameplayAbilitySystem
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	// Initialization
	virtual void InitializeAttributes() const;
	virtual void InitializeAoCComponents() const;

private:

	bool bIsDead = false;
};
