// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability System/Data/MeleeComboInfo.h"
#include "CombatInterface.generated.h"

class UCombatComponent;
class UTargetComponent;
struct FAnimationDataForBasicAttack;
struct FGameplayTag;
// This class does not need to be modified.
UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AOC_API ICombatInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual int32 GetPlayerLevel() const;
	virtual FVector GetAttackSocketLocation();
	virtual FVector GetOffHandSocketLocation();
	virtual UTargetComponent* GetTargetComponent() = 0;
	virtual float GetDashDistanceForTag(const FGameplayTag& ComboTag);
	virtual void die() = 0;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFaceTarget(const FVector& Location);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWarpTarget(const FVector& Location);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UCombatComponent* GetCombatComponent();
};
