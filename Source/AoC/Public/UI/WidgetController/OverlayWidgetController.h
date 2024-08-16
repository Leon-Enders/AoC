// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AoCWidgetController.h"
#include "OverlayWidgetController.generated.h"

/**
 * 
 */

class UAoCAbilitySystemComponent;
class UAoCUIAbilityDataAsset;
struct FOnAttributeChangeData;


USTRUCT(BlueprintType)
struct FGameplayTagUIRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag MessageTag = FGameplayTag();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText MessageText = FText();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* Image = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<class UAoCUserWidget> MessageWidget;
};

// Delegates



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangedSignature, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeMenuOpenSignature, bool, bOpened);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWidgetMessageSignature, FGameplayTagUIRow, GameplayTagUIRow);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUIAbilityDataSignature, const FAoCUIAbilityData&, AoCUIAbilityData);


UCLASS(BlueprintType, Blueprintable)
class AOC_API UOverlayWidgetController : public UAoCWidgetController
{
	GENERATED_BODY()

public:

	virtual void BroadCastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FWidgetMessageSignature WidgetMessageDelegate;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FUIAbilityDataSignature UIAbilityDataDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FAttributeMenuOpenSignature AttributeOpenDelegate;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxHealthChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnAttributeChangedSignature OnXPRatioChanged;
	
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnPlayerStatChangedSignature OnLevelChanged;
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WidgetData")
	TObjectPtr<UDataTable> MessageWidgetDataTable;
	
	UFUNCTION(BlueprintCallable)
	void InitializeAbilityData();
	
	template<typename T>
	T* GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag);
	
};

//TODO: Having to match Tag.GetTagName() with the name of the Row in the Data Table is prone to errors, find better solution

template<typename T>
T* UOverlayWidgetController::GetDataTableRowByTag(UDataTable* DataTable, const FGameplayTag& Tag)
{
	return DataTable->FindRow<T>(Tag.GetTagName(), TEXT(""));
}

