// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AoCComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAoCComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AOC_API IAoCComponentInterface
{
	GENERATED_BODY()

	// AoCComponents inherit from these
public:

	virtual void InitializeAoCComponent(FName CharacterName) = 0;
};
