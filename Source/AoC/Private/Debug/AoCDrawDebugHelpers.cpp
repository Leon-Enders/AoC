// Copyright by Leon Enders ©, All Rights Reserved.


#include "Debug/AoCDrawDebugHelpers.h"

void UAoCDrawDebugHelpers::DrawDebugEllipsoid(UWorld* World, const FVector& Center, const FVector& Radii,
	const FQuat& Rotation, const FVector& ForwardDirection, const FColor& Color, bool bPersistentLines, float LifeTime,
	uint8 DepthPriority, float Thickness)
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
