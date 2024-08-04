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
	FGameplayTag CooldownTag;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UTexture2D> AbilityIcon;
	
};


UCLASS()
class AOC_API UAoCUIAbilityDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAoCUIAbilityData> AoCUIAbilitiesData;

	FAoCUIAbilityData GetAoCUIAbilityDataByTag(const FGameplayTag& InputTag);
	
};
