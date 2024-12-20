// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Sphere.h"

void AAoCAbilityTargetActor_Sphere::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInSphere(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
		SendTargetDataBacktoServer(Handle, FGameplayTag());
		Super::ConfirmTargeting();
	}
}

void AAoCAbilityTargetActor_Sphere::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInSphere(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}



TArray<TWeakObjectPtr<AActor>> AAoCAbilityTargetActor_Sphere::GetActorsInSphere(const FVector& Origin)
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
		DrawDebugSphere(GetWorld(), Origin, Radius,16, FColor::Green, false, 0.3f);
	}
#endif // ENABLE_DRAW_DEBUG
	return HitActors;
}


void AAoCAbilityTargetActor_Sphere::Tick(float DeltaSeconds)
{
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		DrawDebugSphere(GetWorld(), Origin, Radius,16, FColor::Green, false, 0.025f);
	}
#endif // ENABLE_DRAW_DEBUG
}