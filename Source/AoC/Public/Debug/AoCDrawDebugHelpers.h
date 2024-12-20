// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AoCDrawDebugHelpers.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCDrawDebugHelpers : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static void DrawDebugEllipsoid(UWorld* World, const FVector& Center,const FVector& Radii, const FQuat& Rotation,const FVector& ForwardDirection, const FColor& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);

};
