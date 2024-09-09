// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor.h"
#include "AoCAbilityTargetActor_Targeting.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_Targeting : public AAoCAbilityTargetActor
{
	GENERATED_BODY()

public:
	AAoCAbilityTargetActor_Targeting(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	virtual void StartTargeting(UGameplayAbility* InAbility) override;
	virtual void ConfirmTargeting() override;
	virtual void ConfirmTargetingAndContinue() override;
	
	virtual void Tick(float DeltaSeconds) override;

	
	void AimWithPlayerController(const FVector& TraceStart, FVector& OutTraceEnd,FVector& OutAimDir , bool bIgnorePitch = false) const;
	static bool ClipCameraRayToAbilityRange(FVector CameraLocation, FVector CameraDirection, FVector AbilityCenter, float AbilityRange, FVector& ClippedPosition);


	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Trace)
	float MaxRange;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Cone)
	float ConeAngle;

protected:

	FGameplayAbilityTargetDataHandle MakeTargetData(const TArray<TWeakObjectPtr<AActor>>& Actors) const;
	TArray<FOverlapResult> GetPotentialTargetsInRadius(const FVector& Origin, float SphereRadius);
private:
	TArray<TWeakObjectPtr<AActor>> GetActorsInCone(const FVector& Origin, const FVector& ConeDirection, float ConeHeight);
	TArray<TWeakObjectPtr<AActor>> FindTargetActor(const FVector& Origin);

	void DrawTargetOutline(TWeakObjectPtr<AActor> InHitActor,TWeakObjectPtr<AActor> InLatestHitActors);
};


