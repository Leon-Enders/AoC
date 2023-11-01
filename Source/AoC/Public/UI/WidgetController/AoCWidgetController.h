// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AoCWidgetController.generated.h"

/**
 * 
 */


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, HealthChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, MaxHealthChanged);


class UAbilitySystemComponent;
class UAttributeSet;
struct FOnAttributeChangeData;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* In_PC, APlayerState* In_PS, UAttributeSet* In_AS, UAbilitySystemComponent* In_ASC):
	PC(In_PC), PS(In_PS),AS(In_AS), ASC(In_ASC){}

	UPROPERTY()
	TObjectPtr<APlayerController> PC= nullptr;

	UPROPERTY()
	TObjectPtr<APlayerState> PS= nullptr;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AS= nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> ASC= nullptr;
};


//Depends on Module (Data)



UCLASS(BlueprintType, Blueprintable)
class AOC_API UAoCWidgetController : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category="GAS_Data")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="GAS-Data")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="GAS_Data")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category="GAS-Data")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	void InitWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedSignature;


	UPROPERTY(BlueprintAssignable)
	FOnMaxHealthChangedSignature OnMaxHealthChangedSignature;
	
	void BroadcastInitialValues();
	
	void HealthChange(const FOnAttributeChangeData& Data);
	
	void MaxHealthChange(const FOnAttributeChangeData& Data);
};
