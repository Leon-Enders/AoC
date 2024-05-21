// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/TargetComponent.h"

#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/Data/AoCTargetingInfo.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}

void UTargetComponent::InitializeTargetComponent(FName CharacterName)
{
	if(UAoCTargetingInfo* AoCTargetingInfo = UAoCAbilitySystemLibrary::GetAoCTargetingInfo(GetOwner()))
	{
		const FAoCTargetingData AoCTargetingData = AoCTargetingInfo->RetrieveAoCTargetingData(CharacterName);
		MaxTargetRange = AoCTargetingData.MaxTargetRange;
		TargetQueryClass = AoCTargetingData.TargetQueryClass;
		bIsOwnerAI = AoCTargetingData.bIsOwnerAI;
	}
}

//TODO:: maybe remove the constness here because it may prevent the modification of state to the receiver
AActor* UTargetComponent::GetTarget()const
{
	if(!Target)
	{
		return nullptr;
	}
	return Target;
}

bool UTargetComponent::GetIsTargeting() const
{
	return bHasTarget;
}

void UTargetComponent::FindTarget()
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
		Target = ClosestEnemy;
		bHasTarget = true;
		UpdateTargetComponentServer(this);
	}

	
}

void UTargetComponent::SetTarget(AActor* SetTarget)
{
	if(Target) return;
	Target = SetTarget;
	bHasTarget = true;
}


void UTargetComponent::UpdateTargetComponentServer_Implementation(UTargetComponent* Client_TargetComponent)
{
	if(Client_TargetComponent)
	{
		Target = Client_TargetComponent->Target;
		bHasTarget = Client_TargetComponent->bHasTarget;
	}
}

void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
		//TODO: Target seems to be not nullptr for server
		if(Target!=nullptr && !bIsOwnerAI)
		{
			SetTargetRotation();
		}
	
}

void UTargetComponent::SetTargetRotation() const
{
	const FVector PlayerLocation = GetOwner()->GetActorLocation();
	const FVector TargetLocation = Target->GetActorLocation();
	const FRotator LookAtTargetRotation = UKismetMathLibrary::FindLookAtRotation(PlayerLocation, TargetLocation);
	
	if( APlayerController* PC = UGameplayStatics::GetPlayerController(GetOwner(), 0))
	{
		PC->SetControlRotation(LookAtTargetRotation);
	}
}






