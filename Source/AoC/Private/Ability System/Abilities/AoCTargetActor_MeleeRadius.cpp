// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCTargetActor_MeleeRadius.h"

#include "Abilities/GameplayAbility.h"

AAoCTargetActor_MeleeRadius::AAoCTargetActor_MeleeRadius(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void AAoCTargetActor_MeleeRadius::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformMeleeOverlap(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCTargetActor_MeleeRadius::ConfirmTargetingAndContinue()
{

	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(PerformMeleeOverlap(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCTargetActor_MeleeRadius::Tick(float DeltaSeconds)
{
	if (SourceActor && SourceActor->GetLocalRole() != ENetRole::ROLE_SimulatedProxy)
	
		

#if ENABLE_DRAW_DEBUG
		if (bDebug)
		{	FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
			DrawDebugSphere(GetWorld(), Origin, Radius, 16, FColor::Green);
		}
#endif // ENABLE_DRAW_DEBUG
}


TArray<TWeakObjectPtr<AActor>> AAoCTargetActor_MeleeRadius::PerformMeleeOverlap(const FVector& Origin)
{
	bool bTraceComplex = false;
	
	FCollisionQueryParams Params(SCENE_QUERY_STAT(RadiusTargetingOverlap), bTraceComplex);
	Params.bReturnPhysicalMaterial = false;

	TArray<FOverlapResult> Overlaps;

	SourceActor->GetWorld()->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(Radius), Params);

	TArray<TWeakObjectPtr<AActor>>	HitActors;

	for (int32 i = 0; i < Overlaps.Num(); ++i)
	{
		//Should this check to see if these pawns are in the AimTarget list?
		APawn* PawnActor = Overlaps[i].OverlapObjectHandle.FetchActor<APawn>();
		if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor))
		{
			HitActors.Add(PawnActor);
		}
	}
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		DrawDebugSphere(GetWorld(), Origin, Radius,16, FColor::Green, false, 0.75f);
	}
#endif // ENABLE_DRAW_DEBUG
	return HitActors;
}
