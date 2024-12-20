// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderCrosshair.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCrosshairTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle, const bool, bHit);

UCLASS()
class AOC_API UTargetDataUnderCrosshair : public UAbilityTask
{
	GENERATED_BODY()

public:

	
	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="TargetDataUnderCrosshair", HidePin="OwningAbility", DefaultToSelf="OwningAbility" ,BlueprintInternalUseOnly))
	static UTargetDataUnderCrosshair* CreateTargetDataUnderCrosshair(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FCrosshairTargetDataSignature ValidData;
protected:
	virtual void Activate() override;
	
	void AbilityTargetDataSetCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag);
	void SendCrosshairData();

	bool bBlockedHit = false;
};
