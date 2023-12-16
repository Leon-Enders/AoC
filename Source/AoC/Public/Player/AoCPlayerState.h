// Copyright by Leon Enders ©, All Rights Reserved.

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

	FORCEINLINE float GetPlayerLevel()const{return PlayerLevel;}
	
protected:

	// Gameplay Ability System
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	float PlayerLevel = 1.f;
};
