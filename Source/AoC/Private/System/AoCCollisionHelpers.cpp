// Copyright by Leon Enders ©, All Rights Reserved.


#include "System/AoCCollisionHelpers.h"

bool UAoCCollisionHelpers::IsPointInEllipsoid(const FVector& Point, const FVector& EllipsoidCenter,const FVector& Radii,const FQuat& Rotation,
	const FVector& ForwardDirection)
{
	// Translate the point relative to the ellipsoid center
	FVector RelativePoint = Point - EllipsoidCenter;

	// Apply the rotation to the relative point
	RelativePoint = Rotation.UnrotateVector(RelativePoint);

	// Apply the rotation to the forward direction
	FVector NormForwardDirection = Rotation.UnrotateVector(ForwardDirection.GetSafeNormal());

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

bool UAoCCollisionHelpers::IsPointInCone(const FVector& Point, const FVector& ConeApex, const FVector& ConeDirection, float ConeAngle, float ConeHeight)
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
