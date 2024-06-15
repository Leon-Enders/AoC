// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/AoCComponentInterface.h"
#include "Interaction/AoCTargetingInterface.h"
#include "Interaction/CombatInterface.h"
#include "AoCCharacterBase.generated.h"


class USphereComponent;
class UAoCComboComponent;
class UAoCTargetComponent;
class UAoCSocketManagerComponent;
class UAoCAvatarDataComponent;
class UFloatingBarComponent;
class UMotionWarpingComponent;
class UAbilitySystemComponent;
class UAttributeSet;


UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface, public IAoCComponentInterface, public IAoCTargetingInterface
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
	
	//Interface Overrides


	virtual void OnTargetSet(bool bIsTargeted) override;
	
	virtual bool GetIsDead_Implementation() override;
	virtual void die() override;
	virtual int32 GetPlayerLevel() const override;
	// Handle Character Death for Client and Server
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();
	
	
	// Avatar properties
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UMaterialInstance> TargetOutlineMaterial;
	
	//TODO: This is kind of dumb and error prone, you have to set not only the widget class the component holds but also change the type to the BP Version
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UFloatingBarComponent> HealthBarComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> TargetSystemCollision;
	// Handle Combo
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	// GameplayAbilitySystem
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	// AoC Components

	UPROPERTY(Category="AvatarProperties", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAoCAvatarDataComponent> AvatarDataComponent;
	
	UPROPERTY(Category="AvatarProperties", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAoCSocketManagerComponent> SocketManagerComponent;

	UPROPERTY(Category="AvatarProperties", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAoCTargetComponent> TargetComponent;
	
	TMap<TSubclassOf<UAoCComponent>, UAoCComponent*> AoCComponentsMap;

private:
	void SetupCharacterComponents();
	void SetupAoCComponents();
	
	bool bIsDead = false;
};
