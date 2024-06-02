// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "AoCAbilityTargetActor_MeleeScan.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_MeleeScan : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()

public:
	AAoCAbilityTargetActor_MeleeScan(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void ConfirmTargeting() override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void CancelTargeting() override;

	
	virtual FHitResult PerformTrace(AActor* InSourceActor) override;
};
