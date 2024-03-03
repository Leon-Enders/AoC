// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "MeleeComboInfo.generated.h"

class UGameplayEffect;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FMeleeComboData
{
	GENERATED_BODY()
	

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FName SectionName = FName();

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	float AttackDistance = 0.f;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> NextComboTag;
};



UCLASS()
class AOC_API UMeleeComboInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FMeleeComboData> MeleeComboInfoForTag;

	FMeleeComboData GetMeleeComboInfoByTag(const FGameplayTag& InfoTag);
};
