// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Ellipsoid.h"

#include "Debug/AoCDrawDebugHelpers.h"
#include "System/AoCCollisionHelpers.h"

void AAoCAbilityTargetActor_Ellipsoid::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInEllipsoid(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
		SendTargetDataBacktoServer(Handle, FGameplayTag());
		Super::ConfirmTargeting();
	}
}

void AAoCAbilityTargetActor_Ellipsoid::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInEllipsoid(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}


TArray<TWeakObjectPtr<AActor>> AAoCAbilityTargetActor_Ellipsoid::GetActorsInEllipsoid(const FVector& Origin)
{
	FQuat EllipsoidRotation = StartLocation.GetTargetingTransform().GetRotation();
	FVector EllipsoidDirection = EllipsoidRotation.GetForwardVector();
	
	TArray<TWeakObjectPtr<AActor>>	HitActors;
	float SphereRadius = Radii.GetMax() * 1.5;  // A sphere for the maximum radius of the ellipsoid
	TArray<FOverlapResult> Overlaps = GetPotentialTargets(Origin, SphereRadius);


	for (int32 i = 0; i < Overlaps.Num(); ++i)
	{
		//Should this check to see if these pawns are in the AimTarget list?
		APawn* PawnActor = Overlaps[i].OverlapObjectHandle.FetchActor<APawn>();
		FVector ActorLocation = PawnActor->GetActorLocation();
		if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor) && UAoCCollisionHelpers::IsPointInEllipsoid(ActorLocation,Origin,Radii,EllipsoidRotation, EllipsoidDirection))
		{
			HitActors.Add(PawnActor);
		}
	}
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		UAoCDrawDebugHelpers::DrawDebugEllipsoid(GetWorld(),Origin,Radii,StartLocation.GetTargetingTransform().GetRotation(),StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(), FColor::Green, false, 0.3f);
	}
#endif // ENABLE_DRAW_DEBUG			
	return HitActors;
}


void AAoCAbilityTargetActor_Ellipsoid::Tick(float DeltaSeconds)
{
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{	FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		UAoCDrawDebugHelpers::DrawDebugEllipsoid(GetWorld(),Origin,Radii,StartLocation.GetTargetingTransform().GetRotation(),StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(), FColor::Green, false, 0.025f);
	}
#endif // ENABLE_DRAW_DEBUG
}