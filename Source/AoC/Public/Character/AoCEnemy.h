// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoCCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "AoCEnemy.generated.h"

class UGameplayEffect;
class UAoCAbilitySet;
struct FGameplayTag;
class UBehaviorTree;
class AAoCAIController;
class UWidgetComponent;
/**
 * 
 */

UENUM(BlueprintType)
enum class EEnemyClass : uint8
{
	E_Caster,
	E_Bruiser,
	E_Thief,
};


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
	virtual void OnAvatarDeath(AActor* Killer) override;
	
	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	// AI Behaviour

protected:
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	EEnemyClass EnemyClass = EEnemyClass::E_Bruiser;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AvatarProperties")
	int32 Level = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Movement")
	float BaseWalkSpeed = 300.f;

	bool bIsHitReacting = false;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	
	UPROPERTY()
	TObjectPtr<AAoCAIController> AoCAIController;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TObjectPtr<UAoCAbilitySet> AbilitySet;

	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TSubclassOf<UGameplayEffect> XPRewardEffect;
};



