// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataForDash.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDashTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

UCLASS()
class AOC_API UTargetDataForDash : public UAbilityTask
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="TargetDataForDash", HidePin="OwningAbility", DefaultToSelf="OwningAbility" ,BlueprintInternalUseOnly))
	static UTargetDataForDash* CreateTargetDataForDash(UGameplayAbility* OwningAbility, const float Distance);


	UPROPERTY(BlueprintAssignable)
	FDashTargetDataSignature ValidData;
protected:

	
	void SendDashTargetData();
	virtual void Activate() override;

	void AbilityTargetDataSetCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag);
	float DashDistance = 0.f;
};
