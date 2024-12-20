// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "AocAbilityTargetActor_Trace.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAocAbilityTargetActor_Trace : public AGameplayAbilityTargetActor_Trace
{
	GENERATED_BODY()
	
public:

	virtual void ConfirmTargeting() override;
	virtual FHitResult PerformTrace(AActor* InSourceActor) override;
};
