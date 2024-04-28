// Copyright by Leon Enders ©, All Rights Reserved.


#include "AI/AoCAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

AAoCAIController::AAoCAIController()
{
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComponent");
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviourTreeComponent");
}
