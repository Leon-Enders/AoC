// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponent.h"
#include "RootMotionModifier.h"
#include "AoCTargetComponent.generated.h"

struct FGameplayAbilityTargetDataHandle;
class UAoCTargetingDataAsset;
struct FMotionWarpingTarget;
class UMotionWarpingComponent;

UCLASS( BlueprintType, ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCTargetComponent : public UAoCComponent
{
	GENERATED_BODY()


public:
	
	UAoCTargetComponent();
	virtual void InitializeAoCComponent() override;

	UFUNCTION(BlueprintCallable)
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

	UFUNCTION(BlueprintCallable)
	FGameplayAbilityTargetDataHandle GetTargetDataHandle()const;
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


	FMotionWarpingTarget CurrentWarpingTarget;
	TObjectPtr<UMotionWarpingComponent> OwnerMotionWarpingComponent;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	TObjectPtr<UAoCTargetingDataAsset> TargetingData;
};
