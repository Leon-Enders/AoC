// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbilityTargetActor_Radius.h"
#include "AoCTargetActor_MeleeRadius.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCTargetActor_MeleeRadius : public AGameplayAbilityTargetActor_Radius
{
	GENERATED_BODY()
public:
		AAoCTargetActor_MeleeRadius(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
		virtual void ConfirmTargeting() override;
		virtual void ConfirmTargetingAndContinue() override;
		virtual void Tick(float DeltaSeconds) override;

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = BoxExtent)
	FVector BoxExtent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = ActorsToIgnore)
	TArray<AActor*> ActorsToIgnore;
protected:
	TArray<TWeakObjectPtr<AActor> >	PerformMeleeOverlap(const FVector& Origin);
	TArray<TWeakObjectPtr<AActor> >	PerformMeleeSweep(const FVector& Origin);
	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;
};
