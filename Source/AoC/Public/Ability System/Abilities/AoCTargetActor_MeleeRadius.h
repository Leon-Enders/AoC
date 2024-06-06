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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Radius)
	float ConeAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Radius)
	float ConeHeight;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Radius)
	FVector Radii;

	
protected:
	TArray<TWeakObjectPtr<AActor> >	PerformMeleeOverlap(const FVector& Origin);
	TWeakObjectPtr<AGameplayAbilityWorldReticle> ReticleActor;

private:
	TArray<TWeakObjectPtr<AActor>> GetActorsInCone(const FVector& Origin);
	TArray<TWeakObjectPtr<AActor>> GetActorsInEllipsoid(const FVector& Origin);

	
	TArray<FOverlapResult> GetPotentialTargets(UWorld* World, const FVector& Origin, float SphereRadius);

	bool IsPointInEllipsoid(const FVector& Point, const FVector& EllipsoidCenter, const FVector& ForwardDirection);
	bool IsPointInCone(const FVector& Point, const FVector& ConeApex, const FVector& ConeDirection);


	//Debug Helpers

	void DrawDebugEllipsoid(UWorld* World, const FVector& Center, const FQuat& Rotation,const FVector& ForwardDirection, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

};
