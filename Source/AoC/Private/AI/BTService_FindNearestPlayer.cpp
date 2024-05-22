// Copyright by Leon Enders ©, All Rights Reserved.


#include "AI/BTService_FindNearestPlayer.h"

#include "AI/AoCAIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Character/AoCChampion.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	APawn* OwningPawn = AIOwner->GetPawn();
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	
	
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(OwningPawn, TargetTag, ActorsWithTag);
	
	float NearestDistance = TNumericLimits<float>::Max();
	AActor* TargetActor = nullptr;
	
	for(const auto Actor : ActorsWithTag)
	{
		if (IsValid(Actor) && IsValid(OwningPawn))
		{
			const float Distance = Actor->GetDistanceTo(OwningPawn);
			if( Distance<= NearestDistance)
			{
				NearestDistance = Distance;
				TargetActor = Actor;
			}
		}
	}

	if(TargetActor!=nullptr)
	{
		//TODO: Currently you can only select target once because it returns early if you already have a target
		IAoCTargetingInterface::Execute_SetTarget(AIOwner->GetPawn(),TargetActor);
	}
	

	
	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, TargetActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, NearestDistance);
	
	
}

