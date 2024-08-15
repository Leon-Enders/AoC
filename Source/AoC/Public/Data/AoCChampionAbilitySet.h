// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Data/AoCAbilitySet.h"
#include "AoCChampionAbilitySet.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API UAoCChampionAbilitySet : public UAoCAbilitySet
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "UI Data", meta=(TitleProperty=UI))
	TObjectPtr<UAoCUIAbilityDataAsset> UIAbilityData;

	virtual void GiveToAbilitySystem(UAoCAbilitySystemComponent* AoCASC, FAoCAbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject, const float Level) const override;

private:
	TMap<const FGameplayTag,const FGameplayTag> AbilityTagInputTagMap;
};
