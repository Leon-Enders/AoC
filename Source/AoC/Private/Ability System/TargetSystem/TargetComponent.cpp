// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/TargetSystem/TargetComponent.h"


UTargetComponent::UTargetComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
}

AActor* UTargetComponent::GetTargetEnemy() const
{
	if(!TargetEnemy)
	{
		return nullptr;
	}
	return TargetEnemy;
}

bool UTargetComponent::GetIsTargeting() const
{
	return bIsTargeting;
}

FVector UTargetComponent::GetTargetLocation() const
{
	return TargetEnemy->GetActorLocation();
}

void UTargetComponent::SetTargetEnemy(AActor* Enemy)
{
	TargetEnemy = Enemy;
}

void UTargetComponent::SetIsTargeting(const bool IsTargeting)
{
	bIsTargeting = IsTargeting;
}






