// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AoCAttributeSet.generated.h"

/**
 * 
 */



#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


template<class T>
using TFuncPtr = typename  TBaseStaticDelegateInstance< T, FDefaultDelegateUserPolicy>::FFuncPtr;



DECLARE_MULTICAST_DELEGATE_OneParam(FOnAvatarDeath, AActor* Killer);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnXPReceived, const int32);

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){};
	
	FGameplayEffectContextHandle GameplayEffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;
	
};

UCLASS()
class AOC_API UAoCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAoCAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	void SetupEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);


	FOnXPReceived OnXPReceivedDelegate;
	FOnAvatarDeath OnAvatarDeathDelegate;
	
	//Map GameplayTag to Attribute
	TMap<FGameplayTag, TFuncPtr<FGameplayAttribute()>> TagsToAttribute;
	
	/* Meta Attributes*/

	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category="Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, IncomingXP);
	
	/* Primary Attributes*/ 

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Might", Category="Primary Attributes")
	FGameplayAttributeData Might;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Might);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Agility", Category="Primary Attributes")
	FGameplayAttributeData Agility;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Agility);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Intelligence", Category="Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Vitality", Category="Primary Attributes")
	FGameplayAttributeData Vitality;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Vitality);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Balance", Category="Primary Attributes")
	FGameplayAttributeData Balance;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Balance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Dexterity", Category="Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Dexterity);
	
	
	/* Secondary Attributes*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Power", Category="Secondary Attributes")
	FGameplayAttributeData Power;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Power);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_CritChance", Category="Secondary Attributes")
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, CritChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_CritDamage", Category="Secondary Attributes")
	FGameplayAttributeData CritDamage;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, CritDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_AttackSpeed", Category="Secondary Attributes")
	FGameplayAttributeData AttackSpeed;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, AttackSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_CastSpeed", Category="Secondary Attributes")
	FGameplayAttributeData CastSpeed;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, CastSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Penetration", Category="Secondary Attributes")
	FGameplayAttributeData Penetration;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Penetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_HealingPower", Category="Secondary Attributes")
	FGameplayAttributeData HealingPower;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, HealingPower);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Defense", Category="Secondary Attributes")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Defense);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_DamageReduction", Category="Secondary Attributes")
	FGameplayAttributeData DamageReduction;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, DamageReduction);
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_CooldownReduction", Category="Secondary Attributes")
	FGameplayAttributeData CooldownReduction;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, CooldownReduction);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MovementSpeed", Category="Secondary Attributes")
	FGameplayAttributeData MovementSpeed;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, MovementSpeed);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_AirControl", Category="Secondary Attributes")
	FGameplayAttributeData AirControl;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, AirControl);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Tenacity", Category="Secondary Attributes")
	FGameplayAttributeData Tenacity;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Tenacity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_HealthRegeneration", Category="Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, HealthRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_ManaRegeneration", Category="Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, ManaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Vampirism", Category="Secondary Attributes")
	FGameplayAttributeData Vampirism;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Vampirism);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MaxHealth", Category="Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, MaxHealth);
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MaxMana", Category="Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MaxEnergy", Category="Secondary Attributes")
	FGameplayAttributeData MaxEnergy;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, MaxEnergy);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_MaxRage", Category="Secondary Attributes")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, MaxRage);

	

	
	
	/* Vital Attributes*/ 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Health", Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Mana", Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Energy", Category="Vital Attributes")
	FGameplayAttributeData Energy;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Energy);
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Rage", Category="Vital Attributes")
	FGameplayAttributeData Rage;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Rage);

	

	/* RepNotify Functions*/


	/* Primary */
	UFUNCTION()
	void OnRep_Might(const FGameplayAttributeData& OldMight) const;

	UFUNCTION()
	void OnRep_Agility(const FGameplayAttributeData& OldAgility) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	
	UFUNCTION()
	void OnRep_Vitality(const FGameplayAttributeData& OldVitality) const;

	UFUNCTION()
	void OnRep_Balance(const FGameplayAttributeData& OldBalance) const;
	
	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;
	
	/* Secondary*/

	UFUNCTION()
	void OnRep_CritChance(const FGameplayAttributeData& OldCritChance) const;

	UFUNCTION()
	void OnRep_Power(const FGameplayAttributeData& OldPower) const;

	UFUNCTION()
	void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage) const;

	UFUNCTION()
	void OnRep_AttackSpeed(const FGameplayAttributeData& OldAttackSpeed) const;

	UFUNCTION()
	void OnRep_CastSpeed(const FGameplayAttributeData& OldCastSpeed) const;

	UFUNCTION()
	void OnRep_Penetration(const FGameplayAttributeData& OldPenetration) const;
	
	UFUNCTION()
	void OnRep_HealingPower(const FGameplayAttributeData& OldHealingPower) const;

	UFUNCTION()
	void OnRep_Defense(const FGameplayAttributeData& OldDefense) const;

	UFUNCTION()
	void OnRep_DamageReduction(const FGameplayAttributeData& OldDamageReduction) const;

	UFUNCTION()
	void OnRep_CooldownReduction(const FGameplayAttributeData& OldCooldownReduction) const;

	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed) const;

	UFUNCTION()
	void OnRep_AirControl(const FGameplayAttributeData& OldAirControl) const;

	UFUNCTION()
	void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity) const;

	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;
	
	UFUNCTION()
	void OnRep_Vampirism(const FGameplayAttributeData& OldVampirism) const;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy) const;

	UFUNCTION()
	void OnRep_MaxRage(const FGameplayAttributeData& OldMaxRage) const;

	

	/* Vital Attributes*/
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	
	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldEnergy) const;

	UFUNCTION()
	void OnRep_Rage(const FGameplayAttributeData& OldRage) const;

private:

	void SetFloatingText(const FEffectProperties& Props,const float Damage, const bool IsCriticalHit);
	
};
