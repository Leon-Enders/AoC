// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterClassInfo.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AoCAvatarData.generated.h"

class UNiagaraSystem;




USTRUCT(BlueprintType)
struct FGameplayTagMontage
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AvatarMontage;
	
};



USTRUCT(BlueprintType)
struct FAoCAvatarDataInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UNiagaraSystem> BloodEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TArray<FGameplayTagMontage> TaggedMontages;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	float LifeSpan = 5.f;
};







UCLASS()
class AOC_API UAoCAvatarData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TMap<ECharacterClass, FAoCAvatarDataInfo> AvatarDataByClass;

	FAoCAvatarDataInfo& RetrieveAvatarDataInfo(const ECharacterClass CharacterClass);
};
