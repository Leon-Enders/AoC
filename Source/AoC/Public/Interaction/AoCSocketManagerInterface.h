// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AoCSocketManagerInterface.generated.h"

struct FGameplayTag;



UINTERFACE(MinimalAPI)
class UAoCSocketManagerInterface : public UInterface
{
	GENERATED_BODY()
};


class AOC_API IAoCSocketManagerInterface
{
	GENERATED_BODY()

	// Inherit from this interface to interact with avatar data component
public:
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetMainHandSocketLocation(const FGameplayTag& MontageTag);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetOffHandSocketLocation(const FGameplayTag& MontageTag);
	
};
