// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AoCPlayerController.generated.h"

class UAoCInputConfig;
/**
 * 
 */
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;


UCLASS()
class AOC_API AAoCPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAoCPlayerController();
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void Move(const FInputActionValue& InputActionValue);
	void CamRot(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
private:

	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_CamRot;
	
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_Move;


	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputMappingContext> IMC_Move;


	void ActivateInputPressed(FGameplayTag GameplayTag);
	void ActivateInputReleased(FGameplayTag GameplayTag);
	void ActivateInputHeld(FGameplayTag GameplayTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAoCInputConfig> AoCInputConfig;
};
