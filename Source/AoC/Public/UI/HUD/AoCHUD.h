// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AoCHUD.generated.h"

class UAoCUIAbilityDataAsset;
class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UAoCUserWidget;
struct FWidgetControllerParams;
/**
 * 
 */

UCLASS()
class AOC_API AAoCHUD : public AHUD
{
	GENERATED_BODY()

	

public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UOverlayWidgetController* GetOverlayWidgetController() const;
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);
	
	
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);
	
	
protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TObjectPtr<UAoCUserWidget> OverlayWidget;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAoCUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
	
};
