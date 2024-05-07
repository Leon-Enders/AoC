// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "AoCPlayerController.generated.h"


class UTargetComponent;
class UWidgetComponent;
class UAoCAbilitySystemComponent;
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

	UFUNCTION(Client, Unreliable)
	void ShowDamageText(float Damage, ACharacter* TargetActor, const bool bIsCriticalHit);

	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:


	// Input Actions
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_CamRot;
	
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_Jump;
	
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_OpenMenu;

	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputAction> IA_SetTarget;


	// InputMappingContext
	UPROPERTY(EditAnywhere, Category="Input");
	TObjectPtr<UInputMappingContext> IMC_Move;


	

	//Input Callbacks
	void Move(const FInputActionValue& InputActionValue);
	void CamRot(const FInputActionValue& InputActionValue);
	void OnJump(const FInputActionValue& InputActionValue);
	void OnOpenMenu(const FInputActionValue& InputActionValue);
	void OnFindTarget(const FInputActionValue& InputActionValue);
	
	//GAS-Inputs
	void AbilityInputTagPressed(FGameplayTag GameplayTag);
	void AbilityInputTagReleased(FGameplayTag GameplayTag);
	void AbilityInputTagHeld(FGameplayTag GameplayTag);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<UAoCInputConfig> AoCInputConfig;
	
	UAoCAbilitySystemComponent* GetASC();

	UPROPERTY()
	TObjectPtr<UAoCAbilitySystemComponent> ASC;
	

	//Attribute Menu
	bool bShowMouse = false;

	//ShowDamage Text
	UPROPERTY(EditDefaultsOnly, Category="UI")
	TSubclassOf<UWidgetComponent> DamageTextWidgetComponentClass;
	
	//Soft Target System
	TObjectPtr<UTargetComponent> AvatarTargetComponent;
};
