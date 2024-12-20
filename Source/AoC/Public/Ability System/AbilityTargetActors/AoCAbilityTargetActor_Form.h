// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor.h"
#include "AoCAbilityTargetActor_Form.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_Form : public AAoCAbilityTargetActor
{
	GENERATED_BODY()

public:
	AAoCAbilityTargetActor_Form(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void StartTargeting(UGameplayAbility* InAbility) override;



	virtual void SendTargetDataBacktoServer(const FGameplayAbilityTargetDataHandle& InData, FGameplayTag ApplicationTag);

	
protected:
	

	FGameplayAbilityTargetDataHandle MakeTargetData(const TArray<TWeakObjectPtr<AActor>>& Actors, const FVector& Origin) const;
	TArray<FOverlapResult> GetPotentialTargets(const FVector& Origin, float SphereRadius);

private:
	bool bHasDataBeenSentToServer = false;
};
