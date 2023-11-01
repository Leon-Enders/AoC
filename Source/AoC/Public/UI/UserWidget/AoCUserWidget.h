// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AoCUserWidget.generated.h"

class UAoCWidgetController;
/**
 * 
 */
UCLASS()
class AOC_API UAoCUserWidget : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;

	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* In_WidgetController);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
};
