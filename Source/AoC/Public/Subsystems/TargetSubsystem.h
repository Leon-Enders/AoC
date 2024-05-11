// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TargetSubsystem.generated.h"


enum ETargetRequest
{
	E_SelectTargets,
	E_FilterTargets,
	E_SortTargets
};

class UTargetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRegisterTargetTaskDelegate,ETargetRequest, TargetRequest, UTargetComponent*, TaskOwningComponent);


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
	void RegisterTargetComponent(UTargetComponent* OwnerTargetComponent);


	FRegisterTargetTaskDelegate RegisterTargetTaskSignature;
	void DelegateTargetTask(ETargetRequest TargetRequest, UTargetComponent* TargetComponent);
	
	
	// Update??
	void UpdateTargetingRequests();

	// Tasks
	void SelectTargets(UTargetComponent* OwnerTargetComponent);
	void FilterTargets(UTargetComponent* OwnerTargetComponent);
	void SortTargets(UTargetComponent* OwnerTargetComponent);


private:
	
	
	TArray<UTargetComponent*> TargetComponents;
};
