// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponent.h"
#include "RootMotionModifier.h"
#include "AoCTargetComponent.generated.h"

class UAoCTargetingDataAsset;
struct FMotionWarpingTarget;
class UMotionWarpingComponent;

UCLASS( BlueprintType ,ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCTargetComponent : public UAoCComponent
{
	GENERATED_BODY()


public:
	
	UAoCTargetComponent();
	virtual void InitializeAoCComponent(FName CharacterName) override;
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
	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* SetTarget);

	UFUNCTION(BlueprintCallable)
	void UpdateWarpTargetName(FName WarpTargetName);
protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:

	//TODO: Create CameraManager which handles this with data from TargetComponent
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
	
	// Update Component to Server?? -- is this not rather update the server with the client data?
	UFUNCTION(Client, Reliable)
	void UpdateTargetComponentServer(UAoCTargetComponent* Client_TargetComponent);


	FMotionWarpingTarget CurrentWarpingTarget;
	TObjectPtr<UMotionWarpingComponent> OwnerMotionWarpingComponent;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAoCTargetingDataAsset> TargetingData;
};
