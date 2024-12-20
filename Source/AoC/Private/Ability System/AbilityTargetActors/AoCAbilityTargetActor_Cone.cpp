// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Cone.h"

#include "System/AoCCollisionHelpers.h"

void AAoCAbilityTargetActor_Cone::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInCone(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCAbilityTargetActor_Cone::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInCone(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}



TArray<TWeakObjectPtr<AActor>> AAoCAbilityTargetActor_Cone::GetActorsInCone(const FVector& Origin)
{
	
	FVector ConeDirection = StartLocation.GetTargetingTransform().GetRotation().GetForwardVector();
	
	TArray<TWeakObjectPtr<AActor>>	HitActors;
	float SphereRadius = ConeHeight * 2;  // A rough bounding sphere radius for the cone
	TArray<FOverlapResult> Overlaps = GetPotentialTargets(Origin, SphereRadius);


	for (int32 i = 0; i < Overlaps.Num(); ++i)
	{
		//Should this check to see if these pawns are in the AimTarget list?
		APawn* PawnActor = Overlaps[i].OverlapObjectHandle.FetchActor<APawn>();
		FVector ActorLocation = PawnActor->GetActorLocation();
		if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor) && (UAoCCollisionHelpers::IsPointInCone(ActorLocation, Origin, ConeDirection, ConeAngle, ConeHeight)))
		{
			HitActors.Add(PawnActor);
		}
	}

#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		DrawDebugCone(GetWorld(), Origin, StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(),ConeHeight, FMath::DegreesToRadians(ConeAngle), FMath::DegreesToRadians(ConeAngle), 12, FColor::Green, false, 0.3f);
	}
#endif // ENABLE_DRAW_DEBUG			
	return HitActors;
}


void AAoCAbilityTargetActor_Cone::Tick(float DeltaSeconds)
{
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{	FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		DrawDebugCone(GetWorld(), Origin, StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(),ConeHeight, FMath::DegreesToRadians(ConeAngle), FMath::DegreesToRadians(ConeAngle), 12, FColor::Green, false, 0.025f);
	}
#endif // ENABLE_DRAW_DEBUG
}