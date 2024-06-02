// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCAbilityTargetActor_MeleeScan.h"

#include "KismetTraceUtils.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/LightWeightInstanceSubsystem.h"

AAoCAbilityTargetActor_MeleeScan::AAoCAbilityTargetActor_MeleeScan(const FObjectInitializer& ObjectInitializer)
{
}

void AAoCAbilityTargetActor_MeleeScan::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace(SourceActor));
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCAbilityTargetActor_MeleeScan::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformTrace(SourceActor));
		TargetDataReadyDelegate.Broadcast(Handle);
	}
	
}

void AAoCAbilityTargetActor_MeleeScan::CancelTargeting()
{
	Super::CancelTargeting();
}

FHitResult AAoCAbilityTargetActor_MeleeScan::PerformTrace(AActor* InSourceActor)
{

	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;

	ActorsToIgnore.Add(InSourceActor);

	FCollisionQueryParams Params(SCENE_QUERY_STAT(AGameplayAbilityTargetActor_SingleLineTrace), bTraceComplex);
	Params.bReturnPhysicalMaterial = true;
	Params.AddIgnoredActors(ActorsToIgnore);

	FVector ScanStart = StartLocation.GetTargetingTransform().GetLocation();// InSourceActor->GetActorLocation();
	FVector ScanEnd;
	
	AimForMeleeScan(InSourceActor, ScanStart, ScanEnd);

	FHitResult ReturnHitResult;
	SweepWithFilter(ReturnHitResult, InSourceActor->GetWorld(), Filter, ScanStart, ScanEnd, FQuat::Identity, FCollisionShape::MakeSphere(50.0f), TraceProfile.Name, Params);
	//Default to end of trace line if we don't hit anything.
	if (!ReturnHitResult.bBlockingHit)
	{
		ReturnHitResult.Location = ScanEnd;
	}
	if (AGameplayAbilityWorldReticle* LocalReticleActor = ReticleActor.Get())
	{
		const bool bHitActor = (ReturnHitResult.bBlockingHit && (ReturnHitResult.HitObjectHandle.IsValid()));
		const FVector ReticleLocation = (bHitActor && LocalReticleActor->bSnapToTargetedActor) ? FLightWeightInstanceSubsystem::Get().GetLocation(ReturnHitResult.HitObjectHandle) : ReturnHitResult.Location;

		LocalReticleActor->SetActorLocation(ReticleLocation);
		LocalReticleActor->SetIsTargetAnActor(bHitActor);
	}
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		DrawDebugSweptSphere(GetWorld(), ScanStart, ScanEnd,50.f, FColor::Green);
		//DrawDebugSphere(GetWorld(), TraceEnd, 100.0f, 16, FColor::Green);
	}
#endif // ENABLE_DRAW_DEBUG
	return ReturnHitResult;
}

void AAoCAbilityTargetActor_MeleeScan::AimForMeleeScan(const AActor* InSourceActor, const FVector& SweepStart,
	FVector& OutSweepEnd) const
{
	if (!OwningAbility) // Server and launching client only
		{
		return;
		}

	APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
	check(PC);

	FVector ViewStart;
	FRotator ViewRot;
	PC->GetPlayerViewPoint(ViewStart, ViewRot);

	const FVector ViewDir = ViewRot.Vector();
	FVector ViewEnd = ViewStart + (ViewDir * MaxRange);
	// Starts the scan from the players position
	ClipCameraRayToAbilityRange(ViewStart, ViewDir, SweepStart, MaxRange, ViewEnd);

	
	FVector AdjustedAimDir = (ViewEnd - SweepStart).GetSafeNormal();
	if (AdjustedAimDir.IsZero())
	{
		AdjustedAimDir = ViewDir;
	}

	OutSweepEnd = SweepStart + (AdjustedAimDir * MaxRange);
}
