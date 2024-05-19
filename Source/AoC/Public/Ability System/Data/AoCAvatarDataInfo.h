// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoCDataTypes.h"
#include "AoCAvatarDataInfo.generated.h"


class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FAoCAvatarData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UAnimMontage> DeathMontage;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UNiagaraSystem> BloodEffect;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TArray<FGameplayTagMontage> GameplayTagMontages;
	
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	float LifeSpan = 5.f;
};



UCLASS()
class AOC_API UAoCAvatarDataInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TMap<FName, FAoCAvatarData> AvatarDataByName;

	FAoCAvatarData RetrieveAvatarData(FName CharacterName);
};
