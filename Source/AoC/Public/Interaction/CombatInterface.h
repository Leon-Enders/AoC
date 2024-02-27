// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

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

	virtual int32 GetPlayerLevel();

	virtual FVector GetAttackSocketLocation();

	virtual FVector GetOffHandSocketLocation();

	virtual void die() = 0;
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetFaceTarget(const FVector& Location);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWarpTarget(const FVector& Location);


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitMontage();
	
};
