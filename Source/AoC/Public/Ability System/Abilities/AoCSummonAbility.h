// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Abilities/AoCGameplayAbility.h"
#include "AoCSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCSummonAbility : public UAoCGameplayAbility
{
	GENERATED_BODY()

public:

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilityProperties")
	int NumberMinions = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilityProperties")
	float MinSpawnDistance = 150.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxSpawnDistance = 300.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Category="AbilityProperties",meta=(ClampMin="0.0", ClampMax="360.0", UIMin="0.0", UIMax="360.0"))
	float SpreadAngle = 90.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilityProperties")
	TArray<TSubclassOf<APawn>> MinionsToSpawn;

	
	UFUNCTION(BlueprintCallable)
	TArray<FVector> GetSpawnLocations() const;

	UFUNCTION(BlueprintPure)
	TSubclassOf<APawn> GetRandomMinionClass() const;
};
