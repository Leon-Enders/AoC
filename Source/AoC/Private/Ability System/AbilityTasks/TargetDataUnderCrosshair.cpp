// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataUnderCrosshair.h"

#include "AbilitySystemComponent.h"
#include "Kismet/GameplayStatics.h"


UTargetDataUnderCrosshair* UTargetDataUnderCrosshair::CreateTargetDataUnderCrosshair(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderCrosshair* MyObj = NewAbilityTask<UTargetDataUnderCrosshair>(OwningAbility);
	return MyObj;
}

void UTargetDataUnderCrosshair::Activate()
{

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendCrosshairData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataUnderCrosshair::AbilityTargetDataSetCallback);
		AbilitySystemComponent->CallAllReplicatedDelegatesIfSet(AbilitySpecHandle,ActivationPredictionKey);

		
	}
	
	
	
	
	
}




void UTargetDataUnderCrosshair::SendCrosshairData()
{
	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());

	
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	
	int width, height = 0;
	PlayerController->GetViewportSize(width,height);

	FVector WorldLocation;
	FVector WorldDirection;
	
	PlayerController->DeprojectScreenPositionToWorld(width/2, height/2,WorldLocation, WorldDirection);
	
	FHitResult CrosshairHit;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActor());
	
	const FVector EndLocation = WorldLocation + (WorldDirection * 10000.f);
	UKismetSystemLibrary::LineTraceSingle(this,
		WorldLocation, EndLocation,TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::None,
		CrosshairHit, true);

	bBlockedHit = CrosshairHit.bBlockingHit;
	
	

	
	
	
	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* GameplayAbilityTargetData = new FGameplayAbilityTargetData_SingleTargetHit();
	FGameplayAbilityTargetData_LocationInfo* GameplayAbilityTargetDataLocation = new FGameplayAbilityTargetData_LocationInfo();
	
	// We still want to fire a projectile even when not hitting somebody
	if(!bBlockedHit)
	{
		
		GameplayAbilityTargetDataLocation->TargetLocation.LiteralTransform.SetLocation(EndLocation);
		GameplayAbilityTargetDataHandle.Add(GameplayAbilityTargetDataLocation);
	}
	
	GameplayAbilityTargetData->HitResult = CrosshairHit;
	GameplayAbilityTargetDataHandle.Add(GameplayAbilityTargetData);
	
	AbilitySystemComponent->ServerSetReplicatedTargetData(
	GetAbilitySpecHandle(),
	GetActivationPredictionKey(),
	GameplayAbilityTargetDataHandle, FGameplayTag(),
			AbilitySystemComponent->ScopedPredictionKey
			);

	
	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(GameplayAbilityTargetDataHandle,bBlockedHit);
	}
}

void UTargetDataUnderCrosshair::AbilityTargetDataSetCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ClearAbilityReplicatedDataCache(GetAbilitySpecHandle(),Ability->GetCurrentActivationInfo());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(AbilityTargetDataHandle, bBlockedHit);
	}
}



