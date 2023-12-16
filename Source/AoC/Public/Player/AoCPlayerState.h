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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	FORCEINLINE int32 GetPlayerLevel()const{return PlayerLevel;}
	
protected:

	// Gameplay Ability System
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_PlayerLevel)
	int32 PlayerLevel = 1;

	UFUNCTION()
	void OnRep_PlayerLevel(int32 OldPlayerLevel);
};
