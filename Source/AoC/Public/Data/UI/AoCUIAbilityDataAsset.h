// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AoCUIAbilityDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAoCUIAbilityData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag CooldownTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag = FGameplayTag();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> AbilityIcon = nullptr;
	
};


UCLASS()
class AOC_API UAoCUIAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	void SetInputTagForData( const FGameplayTag& AbilityTag, const FGameplayTag& InputTag);

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FAoCUIAbilityData> AbilityTagUIAbilitiesMap;
	
};
