// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AoCHUD.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UAoCWidgetController;
class UAoCUserWidget;
/**
 * 
 */
UCLASS()
class AOC_API AAoCHUD : public AHUD
{
	GENERATED_BODY()

	

public:
	
	UAoCWidgetController* GetWidgetController(APlayerController* PC, APlayerState* PS, UAttributeSet* AS, UAbilitySystemComponent* ASC);

	UPROPERTY()
	TObjectPtr<UAoCUserWidget> OverlayWidget;
protected:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAoCUserWidget> OverlayWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UAoCWidgetController> WidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAoCWidgetController> WidgetControllerClass;
	
	
};
