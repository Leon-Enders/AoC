// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "GameplayTagForEffectInfo.generated.h"

class UGameplayEffect;


/**
 * 
 */
UCLASS()
class AOC_API UGameplayTagForEffectInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSubclassOf<UGameplayEffect>> GameplayEffectForTag;

	TSubclassOf<UGameplayEffect>& GetEffectByTag(const FGameplayTag& InfoTag);
};
