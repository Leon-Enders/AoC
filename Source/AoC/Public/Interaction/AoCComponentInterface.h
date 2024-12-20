// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AoCComponentInterface.generated.h"

class UAoCComponent;



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

	// Add Interface to overwrite Getters for AoCComponent
public:

	virtual UAoCComponent* GetAoCComponent(TSubclassOf<UAoCComponent> AoCComponentClass=nullptr) const = 0;
};






