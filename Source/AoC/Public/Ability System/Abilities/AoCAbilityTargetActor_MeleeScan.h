// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Trace.h"
#include "AoCAbilityTargetActor_MeleeScan.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_MeleeScan : public AGameplayAbilityTargetActor
{
	GENERATED_BODY()

public:
	AAoCAbilityTargetActor_MeleeScan(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	virtual void Tick(float DeltaSeconds) override;
protected:

	FGameplayAbilityTargetDataHandle MakeTargetData(const TArray<FHitResult>& HitResults) const;
};
