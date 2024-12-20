// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AttributeInfo.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAoCAttributeInfo
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttributeName = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttributeDescription = FName();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};





UCLASS()
class AOC_API UAttributeInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	FAoCAttributeInfo FindAttributeInfoByTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAoCAttributeInfo> AttributeInfos;
};
