// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Box.h"

#include "Abilities/GameplayAbility.h"
#include "Kismet/KismetSystemLibrary.h"

void AAoCAbilityTargetActor_Box::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInBox(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
		SendTargetDataBacktoServer(Handle, FGameplayTag());
		Super::ConfirmTargeting();
	}
}

void AAoCAbilityTargetActor_Box::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(GetActorsInBox(Origin), Origin);
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}



TArray<TWeakObjectPtr<AActor>> AAoCAbilityTargetActor_Box::GetActorsInBox(const FVector& Origin)
{
	bool bTraceComplex = false;
	FQuat Rotation;
	if(bUseAimRotation)
	{
		APlayerController* PC = OwningAbility->GetCurrentActorInfo()->PlayerController.Get();
		check(PC);
		Rotation = PC->GetControlRotation().Quaternion();
	}
	else
	{
		Rotation = StartLocation.GetTargetingTransform().GetRotation();
	}
	FCollisionQueryParams Params(SCENE_QUERY_STAT(RadiusTargetingOverlap), bTraceComplex);
	Params.bReturnPhysicalMaterial = false;

	TArray<FOverlapResult> Overlaps;

	SourceActor->GetWorld()->OverlapMultiByObjectType(Overlaps, Origin, Rotation, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeBox(BoxHalfExtent), Params);

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
		UKismetSystemLibrary::DrawDebugBox(GetWorld(), Origin, BoxHalfExtent, FColor::Green, Rotation.Rotator(),0.3f,1.f);
		//DrawDebugBox(GetWorld(), Origin, BoxHalfExtent, FColor::Green, false, 0.3f);
	}
#endif // ENABLE_DRAW_DEBUG
	return HitActors;
}

void AAoCAbilityTargetActor_Box::Tick(float DeltaSeconds)
{
#if ENABLE_DRAW_DEBUG
	if (bDebug)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FRotator Rotator = StartLocation.GetTargetingTransform().GetRotation().Rotator();
		UKismetSystemLibrary::DrawDebugBox(GetWorld(), Origin, BoxHalfExtent, FColor::Green, Rotator, 0.3f,1.f);
	}
#endif // ENABLE_DRAW_DEBUG
}