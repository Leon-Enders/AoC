// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "GameFramework/Character.h"
#include "Interaction/AoCAvatarDataInterface.h"
#include "Interaction/AoCSocketManagerInterface.h"
#include "Interaction/AoCTargetingInterface.h"
#include "Interaction/CombatInterface.h"
#include "AoCCharacterBase.generated.h"


class IAoCComponentInterface;

enum class EAoCComponents
{
	TargetComponent,
	AvatarDataComponent,
	ComboComponent,
	SocketManagerComponent
};

class UAoCComponentInterface;
class UTargetComponent;
class UAoCSocketManagerComponent;
class UAoCAvatarDataComponent;
class UComboComponent;
class UFloatingBarComponent;
class UMotionWarpingComponent;
class UAbilitySystemComponent;
class UAttributeSet;



UCLASS()
class AOC_API AAoCCharacterBase : public ACharacter, public IAbilitySystemInterface, public IAoCAvatarDataInterface, public IAoCSocketManagerInterface,public IAoCTargetingInterface, public ICombatInterface
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
	virtual void InitializeAttributes() const;
	virtual void InitializeAoCComponents() const;
	virtual void SetupAoCComponentsMap();
	
	//Combat Interface Overrides
	virtual bool GetIsDead_Implementation() override;
	virtual void die() override;

	// Handle Character Death for Client and Server
	UFUNCTION(NetMulticast, Reliable)
	void MultiCastHandleDeath();
	
	// Avatar Properties
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	FName CharacterName;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;

	TMap<EAoCComponents, IAoCComponentInterface*> AoCComponentsMap;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TObjectPtr<UFloatingBarComponent> HealthBarComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	// GameplayAbilitySystem
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
protected:
	
	//~IAoCAvatarDataInterface
	virtual UAnimMontage* GetHitMontage_Implementation() override;
	virtual UAnimMontage* GetDeathMontage_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual TArray<FGameplayTagMontage> GetGameplayMontages_Implementation() override;
	//~End of IAoCAvatarDataInterface
	
	//~IAoCSocketManagerInterface
	virtual FVector GetMainHandSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	virtual FVector GetOffHandSocketLocation_Implementation(const FGameplayTag& MontageTag) override;
	//~End of IAoCSocketManagerInterface


	//~IAoCTargetingInterface
	virtual bool GetIsTargeting_Implementation() const override;
	virtual AActor* GetTarget_Implementation() override;
	virtual void SetTarget_Implementation(AActor* TargetToSet) override;
	virtual void UpdateWarpTargetName_Implementation(FName WarpTargetName) override;
	virtual void FindTarget_Implementation() override;
	//~End of IAoCTargetingInterface
private:
	
	bool bIsDead = false;
};
