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
	void SetTarget();

	// Update Component Data to Server
	UFUNCTION(Client, Reliable)
	void UpdateTargetComponentServer(UTargetComponent* Client_TargetComponent);

	UFUNCTION(BlueprintCallable)
	AActor* GetTarget() const;

	bool GetIsTargeting() const;

protected:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	
	void SetTargetRotation()const;

	
	UPROPERTY(EditAnywhere, Category="TargetSystem")
	float MaxTargetRange = 1500.f;

	//Soft Target System
	UPROPERTY()
	TObjectPtr<AActor> Target = nullptr;
	bool bHasTarget = false;
	
	UPROPERTY(EditAnywhere, Category="TargetSystem")
	TSubclassOf<AActor> TargetQueryClass;
		
};
