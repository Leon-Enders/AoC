// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AoCTargetingInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UAoCTargetingInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AOC_API IAoCTargetingInterface
{
	GENERATED_BODY()

	// Inherit from this interface to interact with the targetingsubsystem
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool GetIsTargeting() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetTarget();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTarget(AActor* TargetToSet);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdateWarpTargetName(FName WarpTargetName);
	
	//TODO:: Move this into TargetingSubsystem
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void FindTarget();
};
