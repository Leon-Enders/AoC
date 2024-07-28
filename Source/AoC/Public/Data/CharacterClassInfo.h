// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterClassInfo.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
//TODO: Use inheritance and create Champion Classes, Character Classes and Enemy classes enum
UENUM(BlueprintType)
enum class ECharacterClass : uint8
{
	E_Caster,
	E_Bruiser,
	E_Thief,
	C_FireMonk,
	C_FrostMage,
	C_ShadowRogue,
	C_TwoHandWarrior,
	C_DreamWeaver,
	C_MagicArcher,
	C_TheLastOne,
	C_DemonWarrior
};



USTRUCT(BlueprintType)
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TSubclassOf<UGameplayEffect> PrimaryAttributes;

	UPROPERTY(EditDefaultsOnly, Category="Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;
};


UCLASS()
class AOC_API UCharacterClassInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="Character Class Defaults")
	TMap<ECharacterClass, FCharacterClassDefaultInfo> CharacterClassInformation;

	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category="Common Class Defaults")
	TArray<TSubclassOf<UGameplayAbility>> CommonAbilities;
	
	FCharacterClassDefaultInfo GetClassDefaultInfo(ECharacterClass CharacterClass);
};
