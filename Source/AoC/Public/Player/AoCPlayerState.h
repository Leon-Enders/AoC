// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "Data/AoCAbilitySet.h"
#include "AoCPlayerState.generated.h"

/**
 * 
 */

struct FAoCAbilitySet_GrantedHandles;
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
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const {return AttributeSet;}
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	FORCEINLINE const UAoCPawnData* GetPawnData()const{return PawnData;};
	FORCEINLINE const UAoCXPComponent* GetXPComponent()const{return XPComponent;}
	// Initialization of PawnData -> AbilitySet
	void InitializePawnData();

protected:

	// Gameplay Ability System
	UPROPERTY()
	TObjectPtr<UAoCAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"), Category="AbilitySystem")
	TObjectPtr<UAoCXPComponent> XPComponent;
	
	UPROPERTY(EditDefaultsOnly, Category="AbilitySystem")
	TObjectPtr<const UAoCPawnData> PawnData;
private:
	
	void UpdateAbilitySet();
	void OnPlayerLevelChanged(int32 NewLevel);

	
	TArray<FAoCAbilitySet_GrantedHandles> AbilitySetHandles;
};
