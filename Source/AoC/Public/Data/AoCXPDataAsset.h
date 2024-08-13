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
	int32 LevelUpCost;

	UPROPERTY(EditDefaultsOnly)
	int32 AttributePointAward;
	
};



UCLASS()
class AOC_API UAoCXPDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TMap<int32, FAoCXPData> XPDataForLevel;

	FAoCXPData GetXPDataForLevel(const int32 Level) const;
};
