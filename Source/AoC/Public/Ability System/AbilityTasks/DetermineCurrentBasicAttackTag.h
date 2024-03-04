// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "DetermineCurrentBasicAttackTag.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCurrentBasicAttackTagSignature,const FGameplayTag,ActivationTag);


UCLASS()
class AOC_API UDetermineCurrentBasicAttackTag : public UAbilityTask
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="DetermineValidTagData", HidePin="OwningAbility", DefaultToSelf="OwningAbility" ,BlueprintInternalUseOnly))
	static UDetermineCurrentBasicAttackTag* CreateValidTagData(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FCurrentBasicAttackTagSignature ValidTag;

protected:
	void SendValidTagData();
	
	virtual void Activate() override;

	void AbilityTargetDataSetCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag);

	FGameplayTag CurrentBasicAttackTag;
};
