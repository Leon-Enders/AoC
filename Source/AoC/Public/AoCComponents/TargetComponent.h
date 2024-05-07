// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"


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
	AActor* GetTarget() const;

	bool GetIsTargeting() const;


	/*
	 * Setter
	 */
	void SetTarget(AActor* SetTarget);
	void SetIsOwnerAI(bool bIsAI);


protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	// Updates Rotation of the player to the target
	void SetTargetRotation()const;


	// Radius for the Targeting Query
	UPROPERTY(EditAnywhere, Category="TargetSystem")
	float MaxTargetRange = 1500.f;

	//Target System
	UPROPERTY()
	TObjectPtr<AActor> Target = nullptr;
	
	bool bHasTarget = false;

	// What Class of Actors should be queried for
	// TODO: change to find actors by tag
	UPROPERTY(EditAnywhere, Category="TargetSystem")
	TSubclassOf<AActor> TargetQueryClass;


	bool bIsOwnerAI = false;


	// Update Component Data to Server
	UFUNCTION(Client, Reliable)
	void UpdateTargetComponentServer(UTargetComponent* Client_TargetComponent);
};
