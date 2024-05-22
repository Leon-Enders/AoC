// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoCTargetingInfo.generated.h"

/**
 * 
 */



USTRUCT()
struct FAoCTargetingData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	float MaxTargetRange = 1500.f;

	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	TSubclassOf<AActor> TargetQueryClass;

	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	bool bIsOwnerAI = false;

	UPROPERTY(EditAnywhere, Category="TargetSystemDefaults")
	FName DefaultWarpTargetName;
};




UCLASS()
class AOC_API UAoCTargetingInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category="TargetingProperties")
	TMap<FName, FAoCTargetingData> TagToAoCTargetingData;
	
	FAoCTargetingData RetrieveAoCTargetingData(const FName& CharacterName);
};
