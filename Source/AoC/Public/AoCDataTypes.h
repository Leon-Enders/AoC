// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once
#include "GameplayTagContainer.h"
#include "AoCDataTypes.generated.h"


USTRUCT(BlueprintType)
struct FGameplayTagMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AvatarMontage;
	
};