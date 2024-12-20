// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCDataTypes.h"
#include "Engine/DataAsset.h"
#include "AoCAvatarDataAsset.generated.h"


class UNiagaraSystem;
/**
 * 
 */
UCLASS()
class AOC_API UAoCAvatarDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

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
