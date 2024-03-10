// Copyright by Leon Enders ©, All Rights Reserved.


#include "Player/AoCPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/TargetSystem/TargetComponent.h"
#include "Character/AoCCharacterBase.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "Input/AoCInputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UI/Widget/DamageTextComponent.h"
#include "UI/WidgetController/OverlayWidgetController.h"


AAoCPlayerController::AAoCPlayerController()
{
	bReplicates = true;
}

void AAoCPlayerController::ShowDamageText_Implementation(float Damage, ACharacter* TargetCharacter)
{
	UDamageTextComponent* DamageTextWidget = NewObject<UDamageTextComponent>(TargetCharacter,DamageTextWidgetComponentClass);
	DamageTextWidget->RegisterComponent();
	DamageTextWidget->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);
	DamageTextWidget->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	DamageTextWidget->UpdateDamageText(Damage);
	
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

	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetPawn()))
	{
		PlayerTargetComponent = CombatInterface->GetTargetComponent();
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
	AoCInputComponent->BindAction(IA_SetTarget, ETriggerEvent::Completed, this, &AAoCPlayerController::OnSetTargetMenu);


	// GAS - Inputs
	AoCInputComponent->BindAbilityInputTag(AoCInputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
	
	
	
}

void AAoCPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(PlayerTargetComponent != nullptr)
	{
		if(PlayerTargetComponent->GetTargetEnemy()!=nullptr)
		{
			SetTargetRotation();
		}
	}
	
	
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

void AAoCPlayerController::OnSetTargetMenu(const FInputActionValue& InputActionValue)
{
	
	
	if(PlayerTargetComponent->GetTargetEnemy())
	{
		PlayerTargetComponent->SetTargetEnemy(nullptr);
		SetTargetComponentServer(PlayerTargetComponent);
		return;
	}
	
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this,AAoCCharacterBase::StaticClass(),Enemies);
	if(!HasAuthority())
	{
		Enemies.Remove(GetPawn());
	}
	
	const FVector PlayerLocation = GetPawn()->GetActorLocation();
	AActor* ClosestEnemy = Enemies[0];
	
	auto DistanceComparator = [&PlayerLocation, &ClosestEnemy](AActor* NextEnemy) {
		if (NextEnemy == nullptr)
			{
			return false;
		}
		const float DistanceA = FVector::Distance(PlayerLocation, NextEnemy->GetActorLocation());
		const float DistanceB = FVector::Distance(PlayerLocation, ClosestEnemy->GetActorLocation());
		return DistanceA < DistanceB;
	};
	
	for(const auto Enemy : Enemies)
	{
		if(DistanceComparator(Enemy))
		{
			ClosestEnemy = Enemy;
		}
	}
	
	PlayerTargetComponent->SetTargetEnemy(ClosestEnemy);
	SetTargetComponentServer(PlayerTargetComponent);

	
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


void AAoCPlayerController::SetTargetComponentServer_Implementation(UTargetComponent* TargetComponent)
{
	PlayerTargetComponent = TargetComponent;
}

void AAoCPlayerController::SetTargetRotation()
{
	const FVector PlayerLocation = GetPawn()->GetActorLocation();
	const FVector TargetLocation = PlayerTargetComponent->GetTargetEnemy()->GetActorLocation();
	const FRotator LookAtTargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
	SetControlRotation(LookAtTargetRotation);
	
}
