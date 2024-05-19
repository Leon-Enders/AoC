// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AoCDataTypes.h"
#include "AoCAvatarDataInterface.generated.h"


struct FGameplayTagMontage;
class UNiagaraSystem;

UINTERFACE(MinimalAPI)
class UAoCAvatarDataInterface : public UInterface
{
	GENERATED_BODY()
};


class AOC_API IAoCAvatarDataInterface
{
	GENERATED_BODY()

	// Inherit from this interface to interact with avatar data component
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetDeathMontage();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FGameplayTagMontage> GetGameplayMontages();
};
