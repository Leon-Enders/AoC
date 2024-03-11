// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/TargetSystem/TargetComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

AActor* UTargetComponent::GetTargetEnemy() const
{
	if(!SoftTarget)
	{
		return nullptr;
	}
	return SoftTarget;
}

bool UTargetComponent::GetIsTargeting() const
{
	return bHasSoftTarget;
}

void UTargetComponent::SetSoftTarget()
{
	if(SoftTarget)
	{
		SoftTarget = nullptr;
		bHasSoftTarget = false;
		UpdateTargetComponentServer(this);
		return;
	}
	
	TArray<AActor*> Enemies;
	UGameplayStatics::GetAllActorsOfClass(this,SoftTargetQueryClass,Enemies);
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
		SoftTarget = ClosestEnemy;
		bHasSoftTarget = true;
		UpdateTargetComponentServer(this);
	}

	
}

void UTargetComponent::UpdateTargetComponentServer_Implementation(UTargetComponent* Client_TargetComponent)
{
	if(Client_TargetComponent)
	{
		SoftTarget = Client_TargetComponent->SoftTarget;
		bHasSoftTarget = Client_TargetComponent->bHasSoftTarget;
	}
}

void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
		if(SoftTarget!=nullptr)
		{
			SetSoftTargetRotation();
		}
	
}

void UTargetComponent::SetSoftTargetRotation() const
{
	const FVector PlayerLocation = GetOwner()->GetActorLocation();
	const FVector TargetLocation = SoftTarget->GetActorLocation();
	const FRotator LookAtTargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
	
	if( APlayerController* PC = UGameplayStatics::GetPlayerController(GetOwner(), 0))
	{
		PC->SetControlRotation(LookAtTargetRotation);
	}
}






