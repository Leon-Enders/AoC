// Copyright by Leon Enders ©, All Rights Reserved.


#include "Player/AoCPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "AoCComponents/CombatComponent.h"
#include "Character/AoCCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Input/AoCInputComponent.h"
#include "UI/WidgetComponent/DamageTextComponent.h"
#include "AoCComponents/TargetComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"


AAoCPlayerController::AAoCPlayerController()
{
	bReplicates = true;
}



void AAoCPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(IMC_Move);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(IMC_Move,0);
	}

	// Initialize TargetComponent of the avatar
	if(GetPawn())
	{
		AvatarTargetComponent = ICombatInterface::Execute_GetTargetComponent(GetPawn()->GetComponentByClass<UCombatComponent>());
	}
	
	
	
}

void AAoCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(IA_Move);
	check(IA_CamRot);
	check(AoCInputConfig);
	UAoCInputComponent* AoCInputComponent = CastChecked<UAoCInputComponent>(InputComponent);

	
	//Inputs
	AoCInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered,this, &AAoCPlayerController::Move);
	AoCInputComponent->BindAction(IA_CamRot, ETriggerEvent::Triggered,this, &AAoCPlayerController::CamRot);
	AoCInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AAoCPlayerController::OnJump);
	AoCInputComponent->BindAction(IA_OpenMenu, ETriggerEvent::Completed, this, &AAoCPlayerController::OnOpenMenu);
	AoCInputComponent->BindAction(IA_SetTarget, ETriggerEvent::Completed, this, &AAoCPlayerController::OnFindTarget);


	// GAS - Inputs
	AoCInputComponent->BindAbilityInputTag(AoCInputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	
	
}


void AAoCPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D vel = InputActionValue.Get<FVector2D>();
	
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation = FRotator(0.f, Rotation.Yaw,0.f);
	
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(Forward, vel.Y);
		ControlledPawn->AddMovementInput(Right, vel.X);
	}
	
}

void AAoCPlayerController::CamRot(const FInputActionValue& InputActionValue)
{
	const FVector2D dir = InputActionValue.Get<FVector2D>();
	FRotator Rotation = GetControlRotation();
	Rotation.Pitch += dir.Y;
	Rotation.Yaw += dir.X;
	SetControlRotation(Rotation);
	
	
}

void AAoCPlayerController::OnJump(const FInputActionValue& InputActionValue)
{
	if(ACharacter* ControlledPawn = GetPawn<ACharacter>())
	{
		ControlledPawn->Jump();
	}
}

void AAoCPlayerController::OnOpenMenu(const FInputActionValue& InputActionValue)
{

	const UOverlayWidgetController* OverlayWidgetController = UAoCAbilitySystemLibrary::GetOverlayWidgetController(this);
	
	if(!bShowMouse)
	{
		bShowMouse=true;
		SetInputMode(FInputModeGameAndUI());
		SetShowMouseCursor(true);
		if(OverlayWidgetController)
		{
			OverlayWidgetController->AttributeOpenDelegate.Broadcast(true);
		}
	}
	else
	{
		bShowMouse=false;
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());
		if(OverlayWidgetController)
		{
			OverlayWidgetController->AttributeOpenDelegate.Broadcast(false);
		}
	}
}

void AAoCPlayerController::OnFindTarget(const FInputActionValue& InputActionValue)
{
	AvatarTargetComponent->FindTarget();
}

void AAoCPlayerController::AbilityInputTagPressed(FGameplayTag GameplayTag)
{
	
}

void AAoCPlayerController::AbilityInputTagReleased(FGameplayTag GameplayTag)
{
	if(GetASC())
	{
		GetASC()->ActivateInputReleased(GameplayTag);
	}

	
}

void AAoCPlayerController::AbilityInputTagHeld(FGameplayTag GameplayTag)
{
	if(GetASC())
	{
		GetASC()->ActivateInputHeld(GameplayTag);
	}
	
}

UAoCAbilitySystemComponent* AAoCPlayerController::GetASC()
{

	if(ASC == nullptr)
	{
		ASC = Cast<UAoCAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return ASC;

}


void AAoCPlayerController::ShowDamageText_Implementation(float Damage, ACharacter* TargetCharacter, const bool bIsCriticalHit)
{
	UDamageTextComponent* DamageTextWidget = NewObject<UDamageTextComponent>(TargetCharacter,DamageTextWidgetComponentClass);
	DamageTextWidget->RegisterComponent();
	DamageTextWidget->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	DamageTextWidget->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	DamageTextWidget->UpdateDamageText(Damage, bIsCriticalHit);
	
}