// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AoCAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
enum class ECharacterClass : uint8;
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

	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemComponent | Character Class Defaults")
	static void InitializeAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent);

	static void InitializeCommonAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent);
};
