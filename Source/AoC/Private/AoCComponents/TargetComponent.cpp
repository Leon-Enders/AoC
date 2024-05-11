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



//TODO:: maybe remove the constness here because it may prevent the modification of state to the receiver
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

TArray<AActor*>& UTargetComponent::GetTargets()
{
	return Targets;
}


void UTargetComponent::UpdateTargetComponentServer_Implementation(UTargetComponent* Client_TargetComponent)
{
	if(Client_TargetComponent)
	{
		MainTarget = Client_TargetComponent->MainTarget;
		bHasTarget = Client_TargetComponent->bHasTarget;
	}
}

void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
		//TODO: Target seems to be not nullptr for server
		if(MainTarget!=nullptr && !bIsOwnerAI)
		{
			SetTargetRotation();
		}
	
}

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







