// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TargetSubsystem.generated.h"

class UTargetComponent;
/**
 * 
 */
UCLASS()
class AOC_API UTargetSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void UpdateTargetingRequests();
	
	void RegisterTargetComponent(UTargetComponent* TargetComponent);
	
	void SelectTargets(TArray<AActor*>&  OutActors, UTargetComponent* OwnerTargetComponent);
	void FilterTargets(TArray<AActor*>&  OutActors, UTargetComponent* OwnerTargetComponent);
	void SortTargets(TArray<AActor*>&  OutActors,UTargetComponent* OwnerTargetComponent);
private:
	
	TArray<UTargetComponent*> TargetComponents;
};
