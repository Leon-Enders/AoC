// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataForBasicAttack.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBasicAttackTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);



UCLASS()
class AOC_API UTargetDataForBasicAttack : public UAbilityTask
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="TargetDataForBasicAttack", HidePin="OwningAbility", DefaultToSelf="OwningAbility" ,BlueprintInternalUseOnly))
	static UTargetDataForBasicAttack* CreateTargetDataForDash(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FBasicAttackTargetDataSignature ValidData;

protected:
	void SendBasicAttackTargetData();
	
	virtual void Activate() override;

	void AbilityTargetDataSetCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag);

	
};
