// Created by Leon Enders

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AoCPlayerController.generated.h"

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

private:

	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_CamRot;
	
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_Move;

	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputMappingContext> IMC_Move;
};
