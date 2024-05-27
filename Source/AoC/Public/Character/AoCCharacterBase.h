// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/AoCComponentInterface.h"
#include "Interaction/CombatInterface.h"
#include "AoCCharacterBase.generated.h"



class UFloatingBarComponent;
class UMotionWarpingComponent;
class UAbilitySystemComponent;
class UAttributeSet;


UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface, public IAoCComponentInterface
{
	GENERATED_BODY()

public:
	AAoCCharacterBase();

	/*
	 * Getters
	 */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAoCComponent* GetAoCComponent(TSubclassOf<UAoCComponent> AoCComponentClass) const override;
	UAttributeSet* GetAttributeSet() const{return AttributeSet;}
	
	
protected:
	
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	virtual void InitializeAttributes() const;
	virtual void InitializeAoCComponents() const;
	
	//Combat Interface Overrides
	
	virtual bool GetIsDead_Implementation() override;
	virtual void die() override;
	virtual int32 GetPlayerLevel() const override;
	// Handle Character Death for Client and Server
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();
	
	
	// Avatar properties
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	FName CharacterName;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UFloatingBarComponent> HealthBarComponent;
	
	// Handle Combo
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	// GameplayAbilitySystem
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	// Add AoCComponents to this Map
	
	UPROPERTY()
	TMap<TSubclassOf<UAoCComponent>,UAoCComponent*> AoCComponentClassesToComponent;

private:
	void SetupCharacterComponents();
	void SetupAoCComponents();
	
	bool bIsDead = false;
};
