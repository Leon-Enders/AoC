// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"



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

	
public:
	
	virtual void die() = 0;
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool GetIsDead();

	
};
