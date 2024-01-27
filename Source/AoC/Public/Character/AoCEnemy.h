// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AoCCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AoCEnemy.generated.h"

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


protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

	virtual int32 GetPlayerLevel() override;


	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBarWidget;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Character Class Defaults")
	int32 Level = 1;


	
};
