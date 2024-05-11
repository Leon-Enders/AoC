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

	TargetSubsystem->RegisterTargetTaskSignature.Broadcast(E_SelectTargets, this);
	
	if(MainTarget)
	{
		MainTarget = nullptr;
		bHasTarget = false;
		UpdateTargetComponentServer(this);
		return;
	}
	
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this,TargetQueryClass,Enemies);
	if(GetOwnerRole() != ROLE_Authority)
	{
		Enemies.Remove(GetOwner());
	}
	
	
	
	const FVector PlayerLocation = GetOwner()->GetActorLocation();
	//TODO:: check for valid Enemies array, Set Target even when only one enemy is in the array
	AActor* ClosestEnemy = nullptr;
	
	auto DistanceComparator = [&](const AActor* NextEnemy) {
		if (NextEnemy == nullptr)
		{
			return false;
		}
		const float DistanceA = FVector::Distance(PlayerLocation, NextEnemy->GetActorLocation());
		if(MaxTargetRange<DistanceA)
		{
			return false;
		}
		if(ClosestEnemy == nullptr)
		{
			return true;
		}
		const float DistanceB = FVector::Distance(PlayerLocation, ClosestEnemy->GetActorLocation());
		return DistanceA < DistanceB;
	};

	bool bEnemyInRange = false;
	for(const auto Enemy : Enemies)
	{
		if(DistanceComparator(Enemy))
		{
			ClosestEnemy = Enemy;
			bEnemyInRange = true;
		}
	}

	if(bEnemyInRange)
	{
		MainTarget = ClosestEnemy;
		bHasTarget = true;
		UpdateTargetComponentServer(this);
	}

	
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







