// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Targeting.h"
#include "Abilities/GameplayAbility.h"
#include "Character/AoCCharacterBase.h"
#include "System/AoCCollisionHelpers.h"

AAoCAbilityTargetActor_Targeting::AAoCAbilityTargetActor_Targeting(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	ShouldProduceTargetDataOnServer = true;
}

void AAoCAbilityTargetActor_Targeting::StartTargeting(UGameplayAbility* InAbility)
{
	Super::StartTargeting(InAbility);
	SourceActor = InAbility->GetCurrentActorInfo()->AvatarActor.Get();
}

void AAoCAbilityTargetActor_Targeting::ConfirmTargeting()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(FindTargetActor(Origin));
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}

void AAoCAbilityTargetActor_Targeting::ConfirmTargetingAndContinue()
{
	check(ShouldProduceTargetData());
	if (SourceActor)
	{
		FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
		FGameplayAbilityTargetDataHandle Handle = MakeTargetData(FindTargetActor(Origin));
		TargetDataReadyDelegate.Broadcast(Handle);
	}
}


void AAoCAbilityTargetActor_Targeting::Tick(float DeltaSeconds)
{
	FVector Origin = StartLocation.GetTargetingTransform().GetLocation();
	TArray<TWeakObjectPtr<AActor>> TargetActor = FindTargetActor(Origin);

	DrawTargetOutline(ActorsToOutline, TargetActor);
	ActorsToOutline = TargetActor;
}

TArray<TWeakObjectPtr<AActor>> AAoCAbilityTargetActor_Targeting::FindTargetActor(const FVector& Origin)
{

	// First Cone at ground level
	const FVector TraceStart = Origin;// InSourceActor->GetActorLocation();
	FVector TraceEnd;
	FVector AimDir;
	
	AimWithPlayerController(TraceStart, TraceEnd, AimDir);//Effective on server and launching client only
	
	//TODO: using Distance here is maybe bad since its already calculated once
	return GetActorsInCone(TraceStart,AimDir,FVector::Distance(TraceStart,TraceEnd));
	
	
	
}

void AAoCAbilityTargetActor_Targeting::DrawTargetOutline(TArray<TWeakObjectPtr<AActor>> InHitActors,
	TArray<TWeakObjectPtr<AActor>> InLatestHitActors)
{
	for (auto& TargetActor : InHitActors)
	{
		if(TargetActor.IsValid())
		{
			const AAoCCharacterBase* Character = Cast<AAoCCharacterBase>(TargetActor);
			if(USkeletalMeshComponent* Mesh = Character->GetComponentByClass<USkeletalMeshComponent>())
			{
				Mesh->SetOverlayMaterialMaxDrawDistance(1.f);
			}
		
		}
	}
	
	for (auto& TargetActor : InLatestHitActors)
	{
		if(TargetActor.IsValid())
		{
		
			const AAoCCharacterBase* Character = Cast<AAoCCharacterBase>(TargetActor);
			if(USkeletalMeshComponent* Mesh = Character->GetComponentByClass<USkeletalMeshComponent>())
			{
				Mesh->SetOverlayMaterialMaxDrawDistance(0.f);
			}
		}
	}
}


void AAoCAbilityTargetActor_Targeting::AimWithPlayerController(const FVector& TraceStart, FVector& OutTraceEnd, FVector& OutAimDir, bool bIgnorePitch) const
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

	
	FHitResult HitResult;

	//SourceActor->GetWorld()->LineTraceSingleByChannel(HitResult, )
	const bool bUseTraceResult = HitResult.bBlockingHit && (FVector::DistSquared(TraceStart, HitResult.Location) <= (MaxRange * MaxRange));

	const FVector AdjustedEnd = (bUseTraceResult) ? HitResult.Location : ViewEnd;

	FVector AdjustedAimDir = (AdjustedEnd - TraceStart).GetSafeNormal();
	if (AdjustedAimDir.IsZero())
	{
		AdjustedAimDir = ViewDir;
	}

	if (bUseTraceResult)
	{
		FVector OriginalAimDir = (ViewEnd - TraceStart).GetSafeNormal();

		if (!OriginalAimDir.IsZero())
		{
			// Convert to angles and use original pitch
			const FRotator OriginalAimRot = OriginalAimDir.Rotation();

			FRotator AdjustedAimRot = AdjustedAimDir.Rotation();
			AdjustedAimRot.Pitch = OriginalAimRot.Pitch;

			AdjustedAimDir = AdjustedAimRot.Vector();
		}
	}

	OutAimDir = AdjustedAimDir;
	OutTraceEnd = TraceStart + (AdjustedAimDir * MaxRange);
}


FGameplayAbilityTargetDataHandle AAoCAbilityTargetActor_Targeting::MakeTargetData(
	const TArray<TWeakObjectPtr<AActor>>& Actors) const
{
	if (OwningAbility)
	{
		/** Use the source location instead of the literal origin */
		return StartLocation.MakeTargetDataHandleFromActors(Actors, false);
	}

	return FGameplayAbilityTargetDataHandle();
}

TArray<FOverlapResult> AAoCAbilityTargetActor_Targeting::GetPotentialTargetsInRadius(const FVector& Origin, float SphereRadius)
{
	bool bTraceComplex = false;

	FCollisionQueryParams Params(SCENE_QUERY_STAT(RadiusTargetingOverlap), bTraceComplex);
	Params.bReturnPhysicalMaterial = false;

	TArray<FOverlapResult> OverlapResults;
	SourceActor->GetWorld()->OverlapMultiByObjectType(OverlapResults, Origin, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(SphereRadius), Params);
	return OverlapResults;
}



TArray<TWeakObjectPtr<AActor>> AAoCAbilityTargetActor_Targeting::GetActorsInCone(const FVector& Origin,
	const FVector& ConeDirection, float ConeHeight)
{
		
	//FVector ConeDirection = StartLocation.GetTargetingTransform().GetRotation().GetForwardVector();
	
	TArray<TWeakObjectPtr<AActor>>	HitActors;
	float SphereRadius = ConeHeight * 2;  // A rough bounding sphere radius for the cone
	TArray<FOverlapResult> Overlaps = GetPotentialTargetsInRadius(Origin, SphereRadius);


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
		DrawDebugCone(GetWorld(), Origin, ConeDirection,ConeHeight, FMath::DegreesToRadians(ConeAngle), FMath::DegreesToRadians(ConeAngle), 12, FColor::Green, false, 0.05f);
	}
#endif // ENABLE_DRAW_DEBUG			
	return HitActors;
}
