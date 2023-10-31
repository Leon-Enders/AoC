// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AoCHUD.generated.h"

class UAoCWidgetController;
class UAoCUserWidget;
/**
 * 
 */
UCLASS()
class AOC_API AAoCHUD : public AHUD
{
	GENERATED_BODY()

	
//TODO Create Reference Pointers for Widget and Widget Controller and add Widget to Viewport
public:

	virtual void BeginPlay() override;
	
	
	UPROPERTY()
	TObjectPtr<UAoCUserWidget> OverlayWidget;


	UPROPERTY(EditAnywhere)
	TSubclassOf<UAoCUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UAoCWidgetController> WidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAoCWidgetController> WidgetControllerClass;
};
