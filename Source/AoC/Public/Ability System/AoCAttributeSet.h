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
	void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	void OnRep_HealthMax(const FGameplayAttributeData& OldHealthMax);
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana);
	
	UFUNCTION()
	void OnRep_ManaMax(const FGameplayAttributeData& OldManaMax);

	// AttributeData
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Health")
	FGameplayAttributeData Health;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_HealthMax")
	FGameplayAttributeData HealthMax;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_Mana")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing="OnRep_ManaMax")
	FGameplayAttributeData ManaMax;
	
};
