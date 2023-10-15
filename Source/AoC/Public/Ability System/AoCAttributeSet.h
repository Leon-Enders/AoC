// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AoCAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAoCAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
	// RepNotify Functions
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;

	UFUNCTION()
	void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	
	UFUNCTION()
	void OnRep_ManaMax(const FGameplayAttributeData& OldManaMax) const;

	// AttributeData
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Health", Category="Vital Attributes")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_HealthMax", Category="Vital Attributes")
	FGameplayAttributeData HealthMax;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Mana", Category="Vital Attributes")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_ManaMax", Category="Vital Attributes")
	FGameplayAttributeData ManaMax;
	
};
