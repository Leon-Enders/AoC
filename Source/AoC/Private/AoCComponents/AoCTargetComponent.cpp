// Copyright by Leon Enders ©, All Rights Reserved.

#include "AoCComponents/AoCTargetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MotionWarpingComponent.h"
#include "RootMotionModifier.h"
#include "Data/AoCTargetingDataAsset.h"


UAoCTargetComponent::UAoCTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UAoCTargetComponent::InitializeAoCComponent()
{
	// Copy Start Targeting Data from DataAsset, we might want to change variables dynamically later, and we dont want to change the DataAsset
	MaxTargetRange = TargetingData->MaxTargetRange;
	TargetQueryClass = TargetingData->TargetQueryClass;
	bIsOwnerAI = TargetingData->bIsOwnerAI;
	CurrentWarpingTarget.Name = TargetingData->DefaultWarpTargetName;
	OwnerMotionWarpingComponent = GetOwner()->GetComponentByClass<UMotionWarpingComponent>();
	
}


//TODO:: maybe remove the constness here because it may prevent the modification of state to the receiver
AActor* UAoCTargetComponent::GetTarget()const
{
	if(!Target)
	{
		return nullptr;
	}
	return Target;
}

bool UAoCTargetComponent::GetIsTargeting() const
{
	return bHasTarget;
}

void UAoCTargetComponent::FindTarget()
{
	if(Target)
	{
		Target = nullptr;
		bHasTarget = false;
		UpdateTargetComponentServer(this);
		return;
	}
	
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this,TargetQueryClass,Enemies);
	
	Enemies.Remove(GetOwner());
	
	
	
	
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
		Target = ClosestEnemy;
		bHasTarget = true;
		UpdateTargetComponentServer(this);
	}

	
}

void UAoCTargetComponent::SetTarget(AActor* SetTarget)
{
	if(Target) return;
	Target = SetTarget;
	bHasTarget = true;
}

void UAoCTargetComponent::UpdateWarpTargetName(FName WarpTargetName)
{
	CurrentWarpingTarget.Name = WarpTargetName;
}


void UAoCTargetComponent::UpdateTargetComponentServer_Implementation(UAoCTargetComponent* Client_TargetComponent)
{
	if(Client_TargetComponent)
	{
		Target = Client_TargetComponent->Target;
		bHasTarget = Client_TargetComponent->bHasTarget;
	}
}

void UAoCTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(Target!=nullptr)
	{
		CurrentWarpingTarget.Location = Target->GetActorLocation();
		OwnerMotionWarpingComponent->AddOrUpdateWarpTarget(CurrentWarpingTarget);
		if(!bIsOwnerAI)
		{
			
			SetTargetRotation();
		}
	}
	
		
	
}

void UAoCTargetComponent::SetTargetRotation() const
{
	const FVector PlayerLocation = GetOwner()->GetActorLocation();
	const FVector TargetLocation = Target->GetActorLocation();
	const FRotator LookAtTargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
	
	if( APlayerController* PC = UGameplayStatics::GetPlayerController(GetOwner(), 0))
	{
		PC->SetControlRotation(LookAtTargetRotation);
	}
}

