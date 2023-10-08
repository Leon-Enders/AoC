// Created by Leon Enders


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
	check(Subsystem);
	Subsystem->AddMappingContext(IMC_Move,0);
	
}

void AAoCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(IA_Move);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered,this, &AAoCPlayerController::Move);
	
	
}



void AAoCPlayerController::Move(const FInputActionValue& InputActionValue)
{
	FVector2D vel = InputActionValue.Get<FVector2D>();
	
	FRotator Rotation = GetControlRotation();
	FRotator YawRotation = FRotator(0.f, Rotation.Yaw,0.f);
	
	FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X).GetSafeNormal();
	FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y).GetSafeNormal();

	if(ACharacter* AoCCharacter = GetCharacter())
	{
		AoCCharacter->AddMovementInput(Forward, vel.Y);
		AoCCharacter->AddMovementInput(Right, vel.X);
	}
	
}
