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

	
	virtual int32 GetPlayerLevel_Implementation()const override;
	virtual void InitializeAttributes() const override;

protected:
	virtual void InitAbilityActorInfo() override;
	virtual float GetDashDistance_Implementation(const FGameplayTag& ComboTag) override;

	// Initialize custom components here
	virtual void InitializeAoCComponents() const override;
	

	// Gameplay Abilities
	void AddCharacterAbilities()const;
private:
	//TODO: Move this also to data asset, create an data asset for champion abilities + passive abilities and one for enemies
	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;

	UPROPERTY(EditDefaultsOnly, Category="Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpPassiveAbilities;

};
