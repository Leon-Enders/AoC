// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AoCWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */

struct FOnAttributeChangeData;
// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagApplied, const FGameplayEffectSpec&, GameplayEffectSpec);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, MaxHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnManaChangedSignature, float, Mana);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxManaChangedSignature, float, MaxMana);


UCLASS(BlueprintType, Blueprintable)
class AOC_API UOverlayWidgetController : public UAoCWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadCastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GameplayTags")
	FOnGameplayTagApplied OnGameplayTagApplied;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnManaChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaxManaChangedSignature OnMaxManaChanged;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> UIMessageDt;
	
protected:

	void FindRowByTag(const FGameplayEffectSpec& GameplayEffectSpec);
	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};
