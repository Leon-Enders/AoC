// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCTargetActor_MeleeRadius.h"

#include "Abilities/GameplayAbility.h"
#include "Debug/AoCDrawDebugHelpers.h"
#include "System/AoCCollisionHelpers.h"

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
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInEllipsoid(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCTargetActor_MeleeRadius::ConfirmTargetingAndContinue()
{

	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInEllipsoid(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCTargetActor_MeleeRadius::Tick(float DeltaSeconds)
{

#if ENABLE_DRAW_DEBUG
		if (bDebug)
		{	FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
			//DrawDebugCone(GetWorld(), Origin, StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(),ConeHeight, FMath::DegreesToRadians(ConeAngle), FMath::DegreesToRadians(ConeAngle), 12, FColor::Green, false, 0.15f);
			UAoCDrawDebugHelpers::DrawDebugEllipsoid(GetWorld(),Origin,Radii,FQuat::Identity,StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(), FColor::Green, false, 0.15f);
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

TArray<TWeakObjectPtr<AActor>> AAoCTargetActor_MeleeRadius::GetActorsInCone(const FVector& Origin)
{

	FVector ConeApex =  Origin;
	FVector ConeDirection = StartLocation.GetTargetingTransform().GetRotation().GetForwardVector();
	
    

	
	TArray<TWeakObjectPtr<AActor>>	HitActors;
	float SphereRadius = ConeHeight * 2;  // A rough bounding sphere radius for the cone
	TArray<FOverlapResult> Overlaps = GetPotentialTargets(SourceActor->GetWorld(), ConeApex, SphereRadius);


		for (int32 i = 0; i < Overlaps.Num(); ++i)
		{
			//Should this check to see if these pawns are in the AimTarget list?
			APawn* PawnActor = Overlaps[i].OverlapObjectHandle.FetchActor<APawn>();
			FVector ActorLocation = PawnActor->GetActorLocation();
			if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor) && (UAoCCollisionHelpers::IsPointInCone(ActorLocation, ConeApex, ConeDirection, ConeAngle, ConeHeight)))
			{
				HitActors.Add(PawnActor);
			}
	}

	DrawDebugCone(GetWorld(), Origin, StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(),ConeHeight, FMath::DegreesToRadians(ConeAngle), FMath::DegreesToRadians(ConeAngle), 12, FColor::Green, false, 0.75f);
			
	return HitActors;
}

TArray<TWeakObjectPtr<AActor>> AAoCTargetActor_MeleeRadius::GetActorsInEllipsoid(const FVector& Origin)
{
	
	FVector EllipsoidDirection = StartLocation.GetTargetingTransform().GetRotation().GetForwardVector();
	
    

	
	TArray<TWeakObjectPtr<AActor>>	HitActors;
	float SphereRadius = ConeHeight * 2;  // A rough bounding sphere radius for the cone
	TArray<FOverlapResult> Overlaps = GetPotentialTargets(SourceActor->GetWorld(), Origin, SphereRadius);


	for (int32 i = 0; i < Overlaps.Num(); ++i)
	{
		//Should this check to see if these pawns are in the AimTarget list?
		APawn* PawnActor = Overlaps[i].OverlapObjectHandle.FetchActor<APawn>();
		FVector ActorLocation = PawnActor->GetActorLocation();
		if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor) && UAoCCollisionHelpers::IsPointInEllipsoid(ActorLocation,Origin,Radii, EllipsoidDirection))
		{
			HitActors.Add(PawnActor);
		}
	}

	UAoCDrawDebugHelpers::DrawDebugEllipsoid(GetWorld(),Origin,Radii,FQuat::Identity,StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(), FColor::Green, false, 0.15f);
				
	return HitActors;
}

TArray<FOverlapResult> AAoCTargetActor_MeleeRadius::GetPotentialTargets(UWorld* World, const FVector& Origin,
                                                                        float SphereRadius)
{

	bool bTraceComplex = false;
	
	FCollisionQueryParams Params(SCENE_QUERY_STAT(RadiusTargetingOverlap), bTraceComplex);
	Params.bReturnPhysicalMaterial = false;
	
	TArray<FOverlapResult> OverlapResults;

	SourceActor->GetWorld()->OverlapMultiByObjectType(OverlapResults, Origin, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(SphereRadius), Params);


	return OverlapResults;
	
}




