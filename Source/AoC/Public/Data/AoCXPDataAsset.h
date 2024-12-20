// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoCXPDataAsset.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAoCXPData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 LevelUpCost = 0;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward = 0;
	
};



UCLASS()
class AOC_API UAoCXPDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	int32 MaxLevel = 1;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<int32, FAoCXPData> XPDataForLevel;

	FAoCXPData GetXPDataForLevel(const int32 Level) const;
};
