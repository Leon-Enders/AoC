// Copyright by Leon Enders ©, All Rights Reserved.


#include "Player/AoCPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"


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
	
}

void AAoCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(IA_Move);
	check(IA_CamRot);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered,this, &AAoCPlayerController::Move);
	EnhancedInputComponent->BindAction(IA_CamRot, ETriggerEvent::Triggered,this, &AAoCPlayerController::CamRot);
	EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AAoCPlayerController::OnJump);
	
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
