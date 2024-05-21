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
	virtual void InitializeAttributes() const override;
	virtual void InitializeAoCComponents() const override;
	virtual void die() override;

	virtual int32 GetPlayerLevel_Implementation()const override;

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AvatarProperties")
	int32 Level = 1;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float BaseWalkSpeed = 300.f;

	bool bIsHitReacting = false;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	// AI Behaviour

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAoCAIController> AoCAIController;

	
};



