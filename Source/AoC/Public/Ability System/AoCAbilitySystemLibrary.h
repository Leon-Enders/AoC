// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AoCAbilitySystemLibrary.generated.h"

class UOverlayWidgetController;
class UAttributeMenuWidgetController;
/**
 * 
 */
UCLASS(BlueprintType)
class AOC_API UAoCAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintPure, Category="AoCAbilitySystemComponent | WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AoCAbilitySystemComponent | WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
};
