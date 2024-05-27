// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AoCComboInfo.generated.h"



UENUM(BlueprintType)
enum class EComboState : uint8
{
	CS_A UMETA(DisplayName = "Combo State A"),
	CS_B UMETA(DisplayName = "Combo State B"),
	CS_C UMETA(DisplayName = "Combo State C"),
	CS_D UMETA(DisplayName = "Combo State D"),
	CS_E UMETA(DisplayName = "Combo State E"),
	CS_F UMETA(DisplayName = "Combo State F")
};

USTRUCT(BlueprintType)
struct FComboStateTag
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TMap<EComboState, FGameplayTag> ComboStateToGameplayTagMap;
};

USTRUCT()
struct FAoCComboData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, float> MoveDistanceForAttack;

	// The first map maps combo number with a complete combo, a complete combo consists of combo state mapped to tag, the tag is used to call the approbiate gameplay ability, so the first combo gets int8=1, the second 2 etc.
	
	UPROPERTY(EditDefaultsOnly)
	TMap<uint8,FComboStateTag> Combos;
};




UCLASS()
class AOC_API UAoCComboInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FName, FAoCComboData> ComboDataByName;
	
	FAoCComboData RetrieveComboDataByName(const FName& CharacterName);
};
