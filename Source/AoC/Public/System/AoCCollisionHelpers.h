// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "AoCCollisionHelpers.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCCollisionHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="AoCCollisionHelpers")
	static bool IsPointInEllipsoid(const FVector& Point, const FVector& EllipsoidCenter,const FVector& Radii,const FQuat& Rotation, const FVector& ForwardDirection);

	UFUNCTION(BlueprintCallable, Category="AoCCollisionHelpers")
	static bool IsPointInCone(const FVector& Point, const FVector& ConeApex, const FVector& ConeDirection, float ConeAngle, float ConeHeight);
	
};
