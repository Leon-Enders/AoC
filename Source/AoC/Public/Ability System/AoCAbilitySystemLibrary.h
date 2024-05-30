// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCAbilitySystemLibrary.generated.h"


class UAoCComboComponent;
class UAoCSocketManagerComponent;
class UAoCAvatarDataComponent;
class UAoCTargetComponent;
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

	//TODO:: Create Static getters for AoC Components, look on GetAbilitySystemComponent from blueprint library for example, they use AbilitySystemGlobals class
	/*Static Getters*/
	UFUNCTION(BlueprintCallable, Category="AoCAbilitySystemLibrary|AoCDataInfo")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextObject);


	/*AoC Component Retrieval*/
	//TODO: Is it okay to use SourceObject for AoCComponentRetrieval?
	UFUNCTION(BlueprintPure, Category = "AoCAbilitySystemLibrary|AoCDataInfo", Meta=(DefaultToSelf = "Actor"))
	static UAoCTargetComponent* GetTargetComponent(UObject* SourceObject);

	UFUNCTION(BlueprintPure, Category = "AoCAbilitySystemLibrary|AoCDataInfo", Meta=(DefaultToSelf = "Actor"))
	static UAoCComboComponent* GetComboComponent(UObject* SourceObject);

	UFUNCTION(BlueprintPure, Category = "AoCAbilitySystemLibrary|AoCDataInfo", Meta=(DefaultToSelf = "Actor"))
	static UAoCAvatarDataComponent* GetAvatarDataComponent(UObject* SourceObject);

	UFUNCTION(BlueprintPure, Category = "AoCAbilitySystemLibrary|AoCDataInfo", Meta=(DefaultToSelf = "Actor"))
	static UAoCSocketManagerComponent* GetSocketManagerComponent(UObject* SourceObject);
	
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

