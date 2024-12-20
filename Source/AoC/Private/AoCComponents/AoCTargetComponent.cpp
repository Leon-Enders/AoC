// Copyright by Leon Enders ©, All Rights Reserved.

#include "AoCComponents/AoCTargetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "MotionWarpingComponent.h"
#include "RootMotionModifier.h"
#include "Abilities/GameplayAbilityTargetTypes.h"
#include "Data/AoCTargetingDataAsset.h"
#include "Interaction/AoCTargetingInterface.h"


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
		SetTarget(nullptr);
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
		SetTarget(ClosestEnemy);
	}

	
}

void UAoCTargetComponent::SetTarget(AActor* SetTarget)
{
	
	
	if(SetTarget == nullptr)
	{
		if(IAoCTargetingInterface* TargetingInterface = Cast<IAoCTargetingInterface>(Target))
		{
			TargetingInterface->OnTargetSet(false);
		}
		
		Target = nullptr;
		bHasTarget = false;
		return;
	}
	if(Target) return;
	if(IAoCTargetingInterface* TargetingInterface = Cast<IAoCTargetingInterface>(SetTarget))
	{
		TargetingInterface->OnTargetSet(true);
	}
	Target = SetTarget;
	bHasTarget = true;
}

void UAoCTargetComponent::UpdateWarpTargetName(FName WarpTargetName)
{
	CurrentWarpingTarget.Name = WarpTargetName;
}

FGameplayAbilityTargetDataHandle UAoCTargetComponent::GetTargetDataHandle() const
{
	FGameplayAbilityTargetDataHandle TargetDataHandle;
	FGameplayAbilityTargetData_ActorArray* TargetData = new FGameplayAbilityTargetData_ActorArray();

	if(Target == nullptr)
	{
		return TargetDataHandle;
	}
	TargetData->TargetActorArray.Add(Target);
	TargetDataHandle.Add(TargetData);
	return TargetDataHandle;
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

	//TODO: Fix rotation for listen server
	if( APlayerController* PC = UGameplayStatics::GetPlayerController(GetOwner(), 0))
	{
		PC->SetControlRotation(LookAtTargetRotation);
	}
}

