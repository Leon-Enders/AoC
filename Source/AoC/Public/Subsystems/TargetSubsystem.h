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
	

	// Initialization
	void RegisterTargetComponent(UTargetComponent* TargetComponent);

	// Update??
	void UpdateTargetingRequests();

	// Tasks
	void SelectTargets(TArray<AActor*>&  Targets);
	void FilterTargets(TArray<AActor*>&  Targets);
	void SortTargets(TArray<AActor*>&  Targets);


private:
	
	
	TArray<UTargetComponent*> TargetComponents;
};
