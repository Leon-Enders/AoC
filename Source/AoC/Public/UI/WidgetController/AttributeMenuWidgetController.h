// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AoCWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

class UAttributeInfo;
/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FAoCAttributeInfo&, AttributeInfo);

UCLASS(BlueprintType, Blueprintable)
class AOC_API UAttributeMenuWidgetController : public UAoCWidgetController
{
	GENERATED_BODY()

public:

	virtual void BindCallbacksToDependencies() override;
	virtual void BroadCastInitialValue() override;


	UPROPERTY(BlueprintAssignable)
	FAttributeInfoSignature AttributeInfoDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnPlayerStatChangedSignature OnAttributePointsChangeDelegate;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAttributeInfo> AttributeInfos;

private:

	void BroadCastAttributeInfo(const FGameplayAttribute& GameplayAttribute, const FGameplayTag& AttributeTag) const;
	
};
