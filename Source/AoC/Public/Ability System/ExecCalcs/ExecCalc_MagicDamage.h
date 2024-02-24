// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_MagicDamage.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UExecCalc_MagicDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UExecCalc_MagicDamage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
