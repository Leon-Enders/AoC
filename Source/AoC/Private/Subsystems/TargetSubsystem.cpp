// Copyright by Leon Enders ©, All Rights Reserved.


#include "Subsystems/TargetSubsystem.h"

#include "AoCComponents/TargetComponent.h"

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
		for(const auto TargetRequest : TargetComponent->GetTargetRequests())
		{

			TArray<AActor*>& Targets = TargetComponent->GetTargets();
				
			if(TargetRequest==E_SelectTargets)
			{
				SelectTargets(Targets);
				TargetComponent->RemoveTargetRequest(TargetRequest);
			}
			if(TargetRequest==E_FilterTargets)
			{
				FilterTargets(Targets);
				TargetComponent->RemoveTargetRequest(TargetRequest);
			}
			if(TargetRequest==E_SortTargets)
			{
				SortTargets(Targets);
				TargetComponent->RemoveTargetRequest(TargetRequest);
			}
		}
	}
}

void UTargetSubsystem::RegisterTargetComponent(UTargetComponent* TargetComponent)
{
	TargetComponents.Add(TargetComponent);
}

void UTargetSubsystem::SelectTargets(TArray<AActor*>& OutActors)
{
	
}

void UTargetSubsystem::FilterTargets(TArray<AActor*>& OutActors)
{
}

void UTargetSubsystem::SortTargets(TArray<AActor*>& OutActors)
{
}
