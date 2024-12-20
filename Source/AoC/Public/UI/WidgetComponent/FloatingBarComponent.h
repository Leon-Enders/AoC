// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "FloatingBarComponent.generated.h"


class UAoCUserWidget;
class UAoCAbilitySystemComponent;
class UAoCAttributeSet;
// Forward Declarations
struct FOnAttributeChangeData;



// Delegate Declarations
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBarParametersChangedSignature, float, Value);


UCLASS()
class AOC_API UFloatingBarComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UFloatingBarComponent();
	
	void InitializeFloatingBar(UAoCAttributeSet* AttributeSet, UAoCAbilitySystemComponent* AbilitySystemComponent);
	
protected:
	
	// These Delegates will be assigned in the Widget Blueprint this Widget Component handles
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnBarParametersChangedSignature OnHealthChanged;
	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnBarParametersChangedSignature OnMaxHealthChanged;

	
private:

	void BindDelegates();
	TObjectPtr<UAoCAttributeSet> OwnerAttributeSet;
	TObjectPtr<UAoCAbilitySystemComponent> OwnerAbilitySystemComponent;
};
