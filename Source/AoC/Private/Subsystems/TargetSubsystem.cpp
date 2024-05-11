// Copyright by Leon Enders ©, All Rights Reserved.


#include "Subsystems/TargetSubsystem.h"

void UTargetSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UTargetSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void UTargetSubsystem::UpdateTargetingRequests()
{
	for(const auto TargetComponent : TargetComponents)
	{
		
	}
}

void UTargetSubsystem::RegisterTargetComponent(UTargetComponent* TargetComponent)
{
	TargetComponents.Add(TargetComponent);
}

void UTargetSubsystem::SelectTargets(TArray<AActor*>& OutActors, UTargetComponent* OwnerTargetComponent)
{
}

void UTargetSubsystem::FilterTargets(TArray<AActor*>& OutActors, UTargetComponent* OwnerTargetComponent)
{
}

void UTargetSubsystem::SortTargets(TArray<AActor*>& OutActors, UTargetComponent* OwnerTargetComponent)
{
}
