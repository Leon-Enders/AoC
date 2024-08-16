// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoCCharacterBase.h"
#include "AoCChampion.generated.h"


/**
 * 
 */

class UAoCUIAbilityDataAsset;

UCLASS()
class AOC_API AAoCChampion : public AAoCCharacterBase
{
	GENERATED_BODY()

public:
	AAoCChampion();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;


protected:
	
	virtual void InitAbilityActorInfo() override;
	virtual void OnAvatarDeath(AActor* Killer) override;

	UPROPERTY(Category="AvatarProperties", VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAoCComboComponent> ComboComponent;
	
};
