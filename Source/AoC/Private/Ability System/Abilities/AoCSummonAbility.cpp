// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCSummonAbility.h"

#include "Kismet/KismetSystemLibrary.h"

TArray<FVector> UAoCSummonAbility::GetSpawnLocations() const
{
	const FVector ForwardVector = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float deltaSpread = SpreadAngle/NumberMinions;
	
	const FVector LeftSpreadOffset = ForwardVector.RotateAngleAxis(-SpreadAngle/2.f,FVector::UpVector);

	TArray<FVector> SpawnLocations;
	
	for(int32 i = 0; i < NumberMinions; i++)
	{
		const FVector DeltaDirection = LeftSpreadOffset.RotateAngleAxis(deltaSpread * i, FVector::UpVector);
		const FVector SpawnLocation = Location + FMath::RandRange(MinSpawnDistance, MaxSpawnDistance)* DeltaDirection;
		//TODO:: GroundTrace
		SpawnLocations.Add(SpawnLocation);

		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Location,
			Location + DeltaDirection* MaxSpawnDistance, 8.f, FLinearColor::Green, 1.f, 1.f);
	}
	
	
	return SpawnLocations;
}
