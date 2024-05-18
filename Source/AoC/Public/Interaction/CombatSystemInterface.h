// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatSystemInterface.generated.h"

class UCombatComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UCombatSystemInterface : public UInterface
{
	GENERATED_BODY()
};



/**
 * 
 */
class AOC_API ICombatSystemInterface
{
	GENERATED_BODY()

	// Interface for Actors interacting with the CombatSystem
public:
	
	virtual UCombatComponent* GetCombatComponent() const = 0;
	//TODO: Find a better place to handle PlayerLevel
	virtual int32 GetPlayerLevel() const;

	
};
