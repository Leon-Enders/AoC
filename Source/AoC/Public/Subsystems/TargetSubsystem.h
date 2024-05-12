// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TargetSubsystem.generated.h"


//TODO: Implement a template to create assets like gameplay abilities to create data driven target requests

UENUM()
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
	void UnRegisterTargetComponent(UTargetComponent* OwnerTargetComponent);
	FRegisterTargetTaskDelegate RegisterTargetTaskDelegate;


private:
	
	UFUNCTION()
	void DelegateTargetTask(ETargetRequest TargetRequest, UTargetComponent* TargetComponent);

	// Tasks
	void SelectTargets(UTargetComponent* OwnerTargetComponent);
	void FilterTargets(UTargetComponent* OwnerTargetComponent);
	void SortTargets(UTargetComponent* OwnerTargetComponent);
	
	TArray<UTargetComponent*> TargetComponents;
};
