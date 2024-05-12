// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/TargetComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Subsystems/TargetSubsystem.h"


UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if(const UGameInstance* GameInstance = GetWorld()->GetGameInstance())
	{
		TargetSubsystem = GameInstance->GetSubsystem<UTargetSubsystem>();
		TargetSubsystem->RegisterTargetComponent(this);
	}
}


AActor* UTargetComponent::GetMainTarget()const
{
	if(!MainTarget)
	{
		return nullptr;
	}
	return MainTarget;
}

bool UTargetComponent::GetIsTargeting() const
{
	return bHasTarget;
}


void UTargetComponent::FindTarget()
{
	TargetSubsystem->RegisterTargetTaskDelegate.Broadcast(E_SelectTargets, this);
}

void UTargetComponent::SetTarget(AActor* SetTarget)
{
	MainTarget = SetTarget;
	if(MainTarget == nullptr)bHasTarget = false;
	else bHasTarget = true;
}

void UTargetComponent::SetIsOwnerAI(bool bIsAI)
{
	bIsOwnerAI = bIsAI;
}


void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
		if(MainTarget!=nullptr && !bIsOwnerAI)
		{
			SetTargetRotation();
		}
	
}

void UTargetComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	TargetSubsystem->UnRegisterTargetComponent(this);
}

//TODO: Should the camera rotation get set here?
void UTargetComponent::SetTargetRotation() const
{
	const FVector PlayerLocation = GetOwner()->GetActorLocation();
	const FVector TargetLocation = MainTarget->GetActorLocation();
	const FRotator LookAtTargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
	
	if( APlayerController* PC = UGameplayStatics::GetPlayerController(GetOwner(), 0))
	{
		PC->SetControlRotation(LookAtTargetRotation);
	}
}







