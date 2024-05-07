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
	virtual int32 GetPlayerLevel()const override;
	virtual void InitializeAttributes() const override;
	/* End Combat Interface*/
protected:
	virtual void InitAbilityActorInfo() override;
	virtual float GetDashDistanceForTag(const FGameplayTag& ComboTag) override;

	// Initialize custom components here
	virtual void InitializeAoCComponents() const override;
	
	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMeleeComboInfo>MeleeComboInfo;

	// Gameplay Abilities
	void AddCharacterAbilities();

	
private:
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpPassiveAbilities;

};
