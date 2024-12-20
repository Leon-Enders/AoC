// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AoCAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class AOC_API AAoCAIController : public AAIController
{
	GENERATED_BODY()

public:

	AAoCAIController();

protected:

	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
};
