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
	
	// RepNotify Functions
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_ManaMax(const FGameplayAttributeData& OldManaMax) const;

	// AttributeDatayyyyyyyyy
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Health", Category="Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Health);

	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_HealthMax", Category="Vital Attributes")
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, HealthMax);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Mana", Category="Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_ManaMax", Category="Vital Attributes")
	FGameplayAttributeData ManaMax;
	ATTRIBUTE_ACCESSORS(UAoCAttributeSet, ManaMax);
	
};
