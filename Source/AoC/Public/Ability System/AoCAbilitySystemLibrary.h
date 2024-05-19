// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCAbilitySystemLibrary.generated.h"


class UAoCSocketManagerInfo;
class UAoCAvatarDataInfo;
class UCharacterClassInfo;
struct FGameplayEffectContextHandle;
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

	/*UI*/
	UFUNCTION(BlueprintPure, Category="AoCAbilitySystemComponent | WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AoCAbilitySystemComponent | WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextObject);
	
	/*UI ends*/


	/*GAS Initialization*/
	
	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemComponent | Character Class Defaults")
	static void InitializeAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* AbilitySystemComponent);

	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemComponent | Character Class Defaults")
	static void GiveStartUpAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* AbilitySystemComponent, ECharacterClass CharacterClass);
	
	/*GAS Initialization end*/


	/*Static Getters*/
	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|AoCDataInfo")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|AoCDataInfo")
	static UAoCAvatarDataInfo* GetAoCAvatarDataInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category="AuraAbilitySystemLibrary|AoCDataInfo")
	static UAoCSocketManagerInfo* GetAoCSocketManagerInfo(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemComponent | GameplayEffectContext")
	static bool GetIsCriticalHit(const FGameplayEffectContextHandle& GameplayEffectContextHandle);

	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemComponent | GameplayEffectContext")
	static void SetIsCriticalHit(FGameplayEffectContextHandle& GameplayEffectContextHandle, const bool IsCriticalHit);

	/*Static Getters end*/


	/*Game Mechanics*/
	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemComponent | GameMechanics")
	static void GetAllLivePlayersInRadius(const UObject* WorldContextObject, const TArray<AActor*> ActorsToIgnore, TArray<AActor*>& OutActors, float Radius, const FVector& Origin);


	UFUNCTION(BlueprintPure, Category="AoCAbilitySystemComponent | GameMechanics")
	static bool IsNotFriend(AActor* FirstActor, AActor* SecondActor);

};
