// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "AoCInputConfig.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FAoCInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<class UInputAction> InputAction;
};



UCLASS()
class AOC_API UAoCInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:

	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const;
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FAoCInputAction> AbilityInputActions;



};
