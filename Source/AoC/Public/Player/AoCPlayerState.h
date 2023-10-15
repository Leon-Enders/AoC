// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AoCPlayerState.generated.h"

/**
 * 
 */


// Gameplay Ability System
class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class AOC_API AAoCPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	AAoCPlayerState();

private:

	// Gameplay Ability System
	UPROPERTY(BlueprintReadOnly, Category="GameplayAbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="GameplayAbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;
};
