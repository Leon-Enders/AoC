// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoCCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AoCEnemy.generated.h"

class UBehaviorTree;
class AAoCAIController;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class AOC_API AAoCEnemy : public AAoCCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AAoCEnemy();
	virtual void PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual int32 GetPlayerLevel() override;
	virtual void InitializeAttributes() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;

	

	// AI Behaviour

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAoCAIController> AoCAIController;
};
