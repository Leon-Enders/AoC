// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "ExecCalc_PhysicalDamage.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UExecCalc_PhysicalDamage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()


	UExecCalc_PhysicalDamage();
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
