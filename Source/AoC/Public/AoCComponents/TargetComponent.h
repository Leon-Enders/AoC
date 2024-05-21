// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetComponent.generated.h"

//TODO: Rename to AoCTargetComponent
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UTargetComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UTargetComponent();
	void InitializeTargetComponent(FName CharacterName);

	
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


protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	// Updates Rotation of the player to the target
	void SetTargetRotation()const;


	
	

	//Target System
	UPROPERTY()
	TObjectPtr<AActor> Target = nullptr;
	
	bool bHasTarget = false;
	bool bIsOwnerAI = false;
	
	// What Class of Actors should be queried for
	// TODO: change to find actors by tag
	float MaxTargetRange = 1500.f;
	TSubclassOf<AActor> TargetQueryClass;
	
	// Update Component Data to Server
	UFUNCTION(Client, Reliable)
	void UpdateTargetComponentServer(UTargetComponent* Client_TargetComponent);


	
};
