// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoCTargetingDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCTargetingDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	float MaxTargetRange = 1500.f;

	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	TSubclassOf<AActor> TargetQueryClass;

	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	bool bIsOwnerAI = false;

	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	FName DefaultWarpTargetName;
};
