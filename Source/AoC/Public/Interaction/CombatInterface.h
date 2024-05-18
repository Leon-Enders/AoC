// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Ability System/Data/MeleeComboInfo.h"
#include "CombatInterface.generated.h"

class UNiagaraSystem;
class UCombatComponent;
class UTargetComponent;
struct FGameplayTag;


USTRUCT(BlueprintType)
struct FTaggedMontages
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MontageTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UAnimMontage> AttackMontage;
	
};



UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AOC_API ICombatInterface
{
	GENERATED_BODY()

	
public:

	virtual int32 GetPlayerLevel() const;
	virtual float GetDashDistanceForTag(const FGameplayTag& ComboTag);
	virtual void die() = 0;

	//TODO: Rename in SetWarpTargetLocation?
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetWarpTarget(const FVector& Location);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetMainHandSocketLocation(const FGameplayTag MontageTag);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetOffHandSocketLocation(const FGameplayTag MontageTag);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitMontage();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UComboComponent* GetComboComponent();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UTargetComponent* GetTargetComponent();

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	bool GetIsDead();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	TArray<FTaggedMontages> GetTaggedMontages();


	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UNiagaraSystem* GetBloodEffect();
};
