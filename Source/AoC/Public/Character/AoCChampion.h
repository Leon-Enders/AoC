// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoCCharacterBase.h"
#include "AoCChampion.generated.h"

/**
 * 
 */
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
	/* End Combat Interface*/
protected:
	virtual void InitAbilityActorInfo() override;
	
};
