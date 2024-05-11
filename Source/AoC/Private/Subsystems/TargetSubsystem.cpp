// Copyright by Leon Enders ©, All Rights Reserved.


#include "Subsystems/TargetSubsystem.h"

#include "AoCComponents/TargetComponent.h"

void UTargetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RegisterTargetTaskSignature.AddDynamic(this, &UTargetSubsystem::DelegateTargetTask);
}

void UTargetSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTargetSubsystem::DelegateTargetTask(ETargetRequest TargetRequest, UTargetComponent* TargetComponent)
{
	TArray<AActor*>& Targets = TargetComponent->GetTargets();
	
	switch (TargetRequest)
	{
	case E_SelectTargets:
		SelectTargets(TargetComponent);
		break;
	case E_FilterTargets:
		FilterTargets(TargetComponent);
		break;
	case E_SortTargets:
		SortTargets(TargetComponent);
		break;
	default: ;
	}
}

void UTargetSubsystem::UpdateTargetingRequests()
{
	
}

void UTargetSubsystem::RegisterTargetComponent(UTargetComponent* OwnerTargetComponent)
{
	TargetComponents.Add(OwnerTargetComponent);
}

void UTargetSubsystem::SelectTargets(UTargetComponent* OwnerTargetComponent)
{
	if(OwnerTargetComponent->GetMainTarget())
	{
		OwnerTargetComponent->SetTarget(nullptr);
		return;
	}


	// Buffer for all potential targets
	TArray<UTargetComponent*> Targets = TargetComponents;
	for(UTargetComponent* TargetComponent : Targets)
	{
		// Remove the target component of the initiator of the event
		if(TargetComponent == OwnerTargetComponent)
		{
			Targets.Remove(TargetComponent);
		}
	}

	
	const AActor* OwnerAvatar = OwnerTargetComponent->GetOwner();
	UTargetComponent* ClosestTarget = nullptr;
	float NearestDistance = TNumericLimits<float>::Max();
	
	for(UTargetComponent* TargetComponent : Targets)
	{
		float Distance = OwnerAvatar->GetDistanceTo(TargetComponent->GetOwner());
		if(Distance < NearestDistance)
		{
			ClosestTarget = TargetComponent;
			NearestDistance = Distance;
		}
	}

	if(ClosestTarget != nullptr)
	{
		OwnerTargetComponent->SetTarget(ClosestTarget->GetOwner());
	}
}

void UTargetSubsystem::FilterTargets(UTargetComponent* TargetComponent)
{
}

void UTargetSubsystem::SortTargets(UTargetComponent* TargetComponent)
{
}
