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


	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UAoCWidgetController* In_WidgetController);

	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();


protected:
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAoCWidgetController> WidgetController;
	
};
