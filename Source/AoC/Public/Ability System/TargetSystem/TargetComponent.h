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
	
	AActor* GetTargetEnemy() const;
	bool GetIsTargeting() const;
	FVector GetTargetLocation()const;
	
	void SetTargetEnemy(AActor* Enemy);
	void SetIsTargeting(const bool IsTargeting);
	
	
private:
		UPROPERTY()
		TObjectPtr<AActor> TargetEnemy;
		bool bIsTargeting = false;
		
};
