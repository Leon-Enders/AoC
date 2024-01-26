// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/TargetDataUnderCrosshair.h"

#include "Kismet/GameplayStatics.h"


UTargetDataUnderCrosshair* UTargetDataUnderCrosshair::CreateTargetDataUnderCrosshair(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCrosshair* MyObj = NewAbilityTask<UTargetDataUnderCrosshair>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderCrosshair::Activate()
{
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	
	int width, height = 0;
	PlayerController->GetViewportSize(width,height);

	FVector WorldLocation;
	FVector WorldDirection;
	
	PlayerController->DeprojectScreenPositionToWorld(width/2, height/2,WorldLocation, WorldDirection);

	
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActor());
	
	const FVector EndLocation = WorldLocation + (WorldDirection * 10000.f);
	UKismetSystemLibrary::LineTraceSingle(this,
		WorldLocation, EndLocation,TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::ForDuration,
		HitResult, true, FLinearColor::Red);


	// We still want to fire a projectile even when not hitting somebody
	if(!HitResult.bBlockingHit)
	{
		HitResult.ImpactPoint = EndLocation;
	}

	
	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* GameplayAbilityTargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	GameplayAbilityTargetData->HitResult = HitResult;
	GameplayAbilityTargetDataHandle.Add(GameplayAbilityTargetData);
	
	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(GameplayAbilityTargetDataHandle);
	}
	
	
}

void UTargetDataUnderCrosshair::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
	EndTask();
}
