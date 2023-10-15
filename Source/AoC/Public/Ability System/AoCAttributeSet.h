// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AoCAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAoCAttributeSet();

private:

	UPROPERTY(BlueprintReadOnly)
	FGameplayAttributeData Health;
};
