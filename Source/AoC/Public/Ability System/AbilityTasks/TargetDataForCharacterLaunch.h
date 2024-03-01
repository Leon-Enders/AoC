// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "Input/InputStates.h"
#include "TargetDataForCharacterLaunch.generated.h"

/**
 * 
 */





DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FLaunchTargetDataSignature, const FGameplayAbilityTargetDataHandle&, DataHandle, const EInputDirection, LRDirection, const EInputDirection,  FWDirection);

UCLASS()
class AOC_API UTargetDataForCharacterLaunch : public UAbilityTask
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="AbilityTasks", meta=(DisplayName="TargetDataForCharacterLaunch", HidePin="OwningAbility", DefaultToSelf="OwningAbility" ,BlueprintInternalUseOnly))
	static UTargetDataForCharacterLaunch* CreateTargetDataForLaunch(UGameplayAbility* OwningAbility, const float LaunchScale);


	UPROPERTY(BlueprintAssignable)
	FLaunchTargetDataSignature ValidData;

protected:

	
	void SendLaunchTargetData();
	virtual void Activate() override;

	void AbilityTargetDataSetCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag);
	float LaunchScale = 0.f;

	const FVector CalculateDashData();
	
	EInputDirection LRDirection;
	EInputDirection FWDirection;
};
