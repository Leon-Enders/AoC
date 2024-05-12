// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


class UTargetSubsystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTargetComponent();
	void FindTarget();
	
	/*
	 * Getter
	 */
	UFUNCTION(BlueprintCallable)
	AActor* GetMainTarget() const;
	bool GetIsTargeting() const;
	
	/*
	 * Setter
	 */
	void SetTarget(AActor* SetTarget);
	void SetIsOwnerAI(bool bIsAI);

protected:
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
private:

	// Updates Rotation of the player to the target
	void SetTargetRotation()const;
	
	UPROPERTY()
	TObjectPtr<AActor> MainTarget = nullptr;
	
	bool bHasTarget = false;
	bool bIsOwnerAI = false;

	// TargetSubsystem
	TObjectPtr<UTargetSubsystem> TargetSubsystem;
};



