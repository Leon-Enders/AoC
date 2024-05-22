// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AoCGameplayAbility.generated.h"

/**
 * 
 */

class UComboComponent;
class UTargetComponent;
class UAoCSocketManagerComponent;
class UAoCAvatarDataComponent;
struct FAoCGameplayAbilityActorInfo;

UCLASS()
class AOC_API UAoCGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag;

	const FAoCGameplayAbilityActorInfo* GetAoCActorInfo() const;

	UFUNCTION(BlueprintPure)
	const UAoCAvatarDataComponent* GetAvatarDataComponentFromInfo()const;
	UFUNCTION(BlueprintPure)
	const UAoCSocketManagerComponent* GetSocketManagerComponentFromInfo()const;
	UFUNCTION(BlueprintPure)
	const UTargetComponent* GetTargetComponentFromInfo()const;
	UFUNCTION(BlueprintPure)
	const UComboComponent* GetComboComponentFromInfo()const;
	
};
