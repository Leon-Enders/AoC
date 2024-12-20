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
	
	/*AoC Component Retrieval*/
	//TODO: Is it okay to use SourceObject for AoCComponentRetrieval? - Maybe Parent would fit better
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

