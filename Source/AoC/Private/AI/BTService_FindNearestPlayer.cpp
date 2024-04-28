// Copyright by Leon Enders ©, All Rights Reserved.


#include "AI/BTService_FindNearestPlayer.h"

#include "AI/AoCAIController.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

void UBTService_FindNearestPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


	APawn* OwningPawn = AIOwner->GetPawn();
	const FName TargetTag = OwningPawn->ActorHasTag(FName("Player")) ? FName("Enemy") : FName("Player");
	
	
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(this, TargetTag, ActorsWithTag);
	
	float NearestDistance = TNumericLimits<float>::Max();
	AActor* TargetActor = nullptr;
	
	for(const auto actor : ActorsWithTag)
	{
		if(!actor) break;
		float Distance = actor->GetDistanceTo(OwningPawn);
		if( Distance<= NearestDistance)
		{
			NearestDistance = Distance;
			TargetActor = actor;
		}
	}

	UBTFunctionLibrary::SetBlackboardValueAsObject(this, TargetToFollowSelector, TargetActor);
	UBTFunctionLibrary::SetBlackboardValueAsFloat(this, DistanceToTargetSelector, NearestDistance);
	
	
}

