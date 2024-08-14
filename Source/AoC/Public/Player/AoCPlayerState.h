// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AoCPlayerState.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UAoCAbilitySystemComponent;
class UAoCPawnData;
class UAoCXPComponent;
class UAttributeSet;

UCLASS()
class AOC_API AAoCPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAoCPlayerState();

	// Gameplay Ability System
	UFUNCTION(BlueprintCallable, Category = "Lyra|PlayerState")
	UAoCAbilitySystemComponent* GetAoCAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	FORCEINLINE int32 GetPlayerLevel()const{return PlayerLevel;}
	
	// Initialization of PawnData -> AbilitySet
	void InitializePawnData();
	
protected:

	// Gameplay Ability System
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAoCAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="AbilitySystem")
	TObjectPtr<UAoCXPComponent> XPComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="AbilitySystem")
	TObjectPtr<const UAoCPawnData> PawnData;
private:

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_PlayerLevel)
	int32 PlayerLevel = 1;

	UFUNCTION()
	void OnRep_PlayerLevel(int32 OldPlayerLevel);

	
};
