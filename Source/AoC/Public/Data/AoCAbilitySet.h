// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AoCAbilitySet.generated.h"

class UAoCUIAbilityDataAsset;
class UAoCAbilitySystemComponent;
struct FActiveGameplayEffectHandle;
struct FGameplayAbilitySpecHandle;
class UGameplayEffect;
class UAoCGameplayAbility;

/**
 *  TODO: Currently Enemies are setup with an AoCAbilitySet, but since they have no InputTags its not the nicest solution
 */

/**
 * FAoCAbilitySet_GameplayAbility
 *
 *	Data used by the ability set to grant gameplay abilities.
 */


USTRUCT(BlueprintType)
struct FAoCAbilitySet_GameplayAbility
{
	GENERATED_BODY()

public:

	// Gameplay ability to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAoCGameplayAbility> Ability = nullptr;

	// AbilityTag.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "AbilityTag"))
	FGameplayTag AbilityTag;
	
	// InputTag of the Ability.
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	
};


/**
 * FAoCAbilitySet_GameplayEffect
 *
 *	Data used by the ability set to grant gameplay effects.
 */

USTRUCT(BlueprintType)
struct FAoCAbilitySet_GameplayEffect
{
	GENERATED_BODY()

public:

	// Gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;
};

USTRUCT(BlueprintType)
struct FAoCAbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:

	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);

	void TakeFromAbilitySystem(UAoCAbilitySystemComponent* AoCASC);

protected:

	// Handles to the granted abilities.
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	// Handles to the granted gameplay effects.
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;
	
};



UCLASS()
class AOC_API UAoCAbilitySet : public UDataAsset
{
	GENERATED_BODY()

public:
	void GiveToAbilitySystem(UAoCAbilitySystemComponent* AoCASC, FAoCAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr, const float Level = 1.f) const;

	UPROPERTY(EditDefaultsOnly, Category = "UI Data", meta=(TitleProperty=UI))
	TObjectPtr<UAoCUIAbilityDataAsset> UIAbilityData;
protected:
	
	// Gameplay abilities to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FAoCAbilitySet_GameplayAbility> GrantedGameplayAbilities;

	// Gameplay effects to grant when this ability set is granted.
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FAoCAbilitySet_GameplayEffect> GrantedGameplayEffects;
	
	TMap<const FGameplayTag,const FGameplayTag> AbilityTagInputTagMap;
};
