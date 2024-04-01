// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MeleeComboInfo.generated.h"




UCLASS()
class AOC_API UMeleeComboInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, float> DashDistanceDataForTag;
	
	float GetAttackDistanceForTag(const FGameplayTag& ComboTag);
};
