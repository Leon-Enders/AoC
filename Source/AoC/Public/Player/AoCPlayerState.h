// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AoCPlayerState.generated.h"

/**
 * 
 */


// Gameplay Ability System
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AOC_API AAoCPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAoCPlayerState();

	// Gameplay Ability System
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const;
	
private:

	// Gameplay Ability System
	UPROPERTY(BlueprintReadOnly, Category="GameplayAbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="GameplayAbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
};
