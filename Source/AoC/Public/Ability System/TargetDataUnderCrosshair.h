// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderCrosshair.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCrosshairTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle);

UCLASS()
class AOC_API UTargetDataUnderCrosshair : public UAbilityTask
{
	GENERATED_BODY()

public:

	
	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="TargetDataUnderCrosshair", HidePin="OwningAbility", DefaultToSelf="OwningAbility" ,BlueprintInternalUseOnly))
	static UTargetDataUnderCrosshair* CreateTargetDataUnderCrosshair(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FCrosshairTargetDataSignature ValidData;
private:
	void Activate() override;
	void OnDestroy(bool bInOwnerFinished) override;
};
