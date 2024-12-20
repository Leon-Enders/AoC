// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AoCWidgetController.generated.h"

/**
 * 
 */

class UAttributeSet;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerStatChangedSignature, int32, NewValue);

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()
	
	FWidgetControllerParams(){}
	FWidgetControllerParams(APlayerController* In_PC, APlayerState* In_PS, UAttributeSet* In_AS, UAbilitySystemComponent* In_ASC):
	PC(In_PC), PS(In_PS),AS(In_AS), ASC(In_ASC)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PC = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AS = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> ASC = nullptr;
};

UCLASS()
class AOC_API UAoCWidgetController : public UObject
{
	GENERATED_BODY()

public:
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);


	UFUNCTION(BlueprintCallable)
	virtual void BroadCastInitialValue();
	
	virtual void BindCallbacksToDependencies();

	
protected:

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
};
