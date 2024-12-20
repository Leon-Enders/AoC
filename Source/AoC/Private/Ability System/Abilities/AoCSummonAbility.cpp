// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCSummonAbility.h"


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
		FVector SpawnLocation = Location + FMath::RandRange(MinSpawnDistance, MaxSpawnDistance)* DeltaDirection;
		
		FHitResult Hit;
		if(GetWorld()->LineTraceSingleByChannel(Hit, SpawnLocation + FVector(0.f,0.f, 500.f), SpawnLocation + FVector(0.f,0.f,-500.f), ECC_Visibility))
		{
			SpawnLocation = Hit.ImpactPoint;
		}

		SpawnLocations.Add(SpawnLocation);
	}
	
	
	return SpawnLocations;
}

TSubclassOf<APawn> UAoCSummonAbility::GetRandomMinionClass() const
{
	int32 Selection = FMath::RandRange(0, MinionsToSpawn.Num()-1);

	return MinionsToSpawn[Selection];
}
