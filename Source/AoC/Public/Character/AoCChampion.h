// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoCCharacterBase.h"
#include "AoCChampion.generated.h"


/**
 * 
 */
class UMeleeComboInfo;
UCLASS()
class AOC_API AAoCChampion : public AAoCCharacterBase
{
	GENERATED_BODY()

public:
	AAoCChampion();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/* Combat Interface*/
	virtual int32 GetPlayerLevel() override;
	virtual void InitializeAttributes() override;
	/* End Combat Interface*/
protected:
	virtual void InitAbilityActorInfo() override;
	virtual FAnimationDataForBasicAttack GetMeleeComboInfo_Implementation(const FGameplayTag& ComboTag) override;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMeleeComboInfo>MeleeComboInfo;
};
