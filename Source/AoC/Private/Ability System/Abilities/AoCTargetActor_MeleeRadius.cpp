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
			DrawDebugEllipsoid(GetWorld(), Origin, FQuat::Identity, StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(),FColor::Green, false, 0.05f);
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
			if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor) && (IsPointInCone(ActorLocation, ConeApex, ConeDirection)))
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
		if (PawnActor && !HitActors.Contains(PawnActor) && Filter.FilterPassesForActor(PawnActor) && IsPointInEllipsoid(ActorLocation,Origin,EllipsoidDirection))
		{
			HitActors.Add(PawnActor);
		}
	}

	DrawDebugEllipsoid(GetWorld(), Origin,FQuat::Identity,StartLocation.GetTargetingTransform().GetRotation().GetForwardVector(), FColor::Green, false, 0.15f);
				
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

bool AAoCTargetActor_MeleeRadius::IsPointInEllipsoid(const FVector& Point, const FVector& EllipsoidCenter,const FVector& ForwardDirection)
{
	// Translate the point relative to the ellipsoid center
	FVector RelativePoint = Point - EllipsoidCenter;

	// Normalize the forward direction
	FVector NormForwardDirection = ForwardDirection.GetSafeNormal();

	// Ensure the point is on the forward side of the ellipsoid
	if (FVector::DotProduct(RelativePoint, NormForwardDirection) < 0)
	{
		return false;
	}

	// Check if the point lies within the ellipsoid's volume
	float XComponent = FMath::Square(RelativePoint.X / Radii.X);
	float YComponent = FMath::Square(RelativePoint.Y / Radii.Y);
	float ZComponent = FMath::Square(RelativePoint.Z / Radii.Z);

	return (XComponent + YComponent + ZComponent) <= 1.0f;


	
}



bool AAoCTargetActor_MeleeRadius::IsPointInCone(const FVector& Point, const FVector& ConeApex,
                                                const FVector& ConeDirection)
{

	float ConeAngleRad = FMath::DegreesToRadians(ConeAngle);
	
	FVector DirectionToPoint = Point - ConeApex;
	float DistanceToPoint = DirectionToPoint.Size();
    
	if (DistanceToPoint > ConeHeight)
	{
		return false;
	}
    
	DirectionToPoint.Normalize();
	float DotProduct = FVector::DotProduct(DirectionToPoint, ConeDirection);
	float AngleToPoint = FMath::Acos(DotProduct);

	return AngleToPoint <= ConeAngleRad;
}

void AAoCTargetActor_MeleeRadius::DrawDebugEllipsoid(UWorld* World, const FVector& Center,
	const FQuat& Rotation, const FVector& ForwardDirection, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority,
	float Thickness)
{
	const int32 NumSegments = 16; // Number of segments for the sphere approximation
	const float AngleStep = PI / NumSegments;

	for (int32 LatitudeSegment = 0; LatitudeSegment < NumSegments; ++LatitudeSegment)
	{
		float Theta1 = LatitudeSegment * AngleStep - PI / 2;
		float Theta2 = (LatitudeSegment + 1) * AngleStep - PI / 2;

		for (int32 LongitudeSegment = 0; LongitudeSegment < 2 * NumSegments; ++LongitudeSegment)
		{
			float Phi1 = LongitudeSegment * AngleStep;
			float Phi2 = (LongitudeSegment + 1) * AngleStep;

			FVector P0 = Center + Rotation.RotateVector(FVector(Radii.X * FMath::Cos(Theta1) * FMath::Cos(Phi1), Radii.Y * FMath::Cos(Theta1) * FMath::Sin(Phi1), Radii.Z * FMath::Sin(Theta1)));
			FVector P1 = Center + Rotation.RotateVector(FVector(Radii.X * FMath::Cos(Theta2) * FMath::Cos(Phi1), Radii.Y * FMath::Cos(Theta2) * FMath::Sin(Phi1), Radii.Z * FMath::Sin(Theta2)));
			FVector P2 = Center + Rotation.RotateVector(FVector(Radii.X * FMath::Cos(Theta1) * FMath::Cos(Phi2), Radii.Y * FMath::Cos(Theta1) * FMath::Sin(Phi2), Radii.Z * FMath::Sin(Theta1)));
			FVector P3 = Center + Rotation.RotateVector(FVector(Radii.X * FMath::Cos(Theta2) * FMath::Cos(Phi2), Radii.Y * FMath::Cos(Theta2) * FMath::Sin(Phi2), Radii.Z * FMath::Sin(Theta2)));

			if (FVector::DotProduct((P0 - Center).GetSafeNormal(), ForwardDirection) >= 0)
			{
				DrawDebugLine(World, P0, P1, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
				DrawDebugLine(World, P0, P2, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
				DrawDebugLine(World, P1, P3, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
				DrawDebugLine(World, P2, P3, Color, bPersistentLines, LifeTime, DepthPriority, Thickness);
			}
		}
	}
}

