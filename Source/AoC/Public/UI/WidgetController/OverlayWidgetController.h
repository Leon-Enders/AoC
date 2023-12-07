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


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameplayTagApplied, FGameplayTagUIRow, GameplayTagUIRow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, Value);



UCLASS(BlueprintType, Blueprintable)
class AOC_API UOverlayWidgetController : public UAoCWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadCastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnGameplayTagApplied OnGameplayTagApplied;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;
	
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UDataTable> UIMessageDt;

	UFUNCTION()
	void FindRowByTag(const FGameplayEffectSpec& GameplayEffectSpec);
	
protected:

	
	
	void HealthChanged(const FOnAttributeChangeData& Data) const;
	void MaxHealthChanged(const FOnAttributeChangeData& Data) const;
	void ManaChanged(const FOnAttributeChangeData& Data) const;
	void MaxManaChanged(const FOnAttributeChangeData& Data) const;
};


