// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoCPawnData.generated.h"

class UAoCAvatarDataAsset;
class UAoCAbilitySet;
/**
 * UAoCPawnData
 *
 *	Non-mutable data asset that contains properties used to define a pawn.
 */
UCLASS(BlueprintType, Const, Meta = (DisplayName = "AoC Pawn Data", ShortTooltip = "Data asset used to define a Pawn."))
class AOC_API UAoCPawnData : public UDataAsset
{
	GENERATED_BODY()

public:

	// Class to instantiate for this pawn (should usually derive from ALyraPawn or ALyraCharacter).
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AoC|Pawn")
	TSubclassOf<APawn> PawnClass;

	// Ability sets to grant to this pawn's ability system.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AoC|Abilities")
	TArray<TObjectPtr<UAoCAbilitySet>> AbilitySets;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AoC|Pawn")
	//TObjectPtr<UAoCAvatarDataAsset> AvatarDataAsset;
	// What mapping of ability tags to use for actions taking by this pawn
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Abilities")
	//TObjectPtr<ULyraAbilityTagRelationshipMapping> TagRelationshipMapping;

	// Input configuration used by player controlled pawns to create input mappings and bind input actions.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Input")
	//TObjectPtr<ULyraInputConfig> InputConfig;

	// Default camera mode used by player controlled pawns.
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lyra|Camera")
	//TSubclassOf<ULyraCameraMode> DefaultCameraMode;
};
