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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag NextComboTag;
};

USTRUCT(BlueprintType)
struct FAnimationDataForBasicAttack
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag NextBasicAttackTag;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TObjectPtr<UAnimMontage> TagMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TMap<FGameplayTag, FMeleeComboData> MeleeComboDataByTag;
};


UCLASS()
class AOC_API UMeleeComboInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FAnimationDataForBasicAttack> AnimationDataForTag;
	
	FAnimationDataForBasicAttack GetAnimationDataForTag(const FGameplayTag& InfoTag);
};
