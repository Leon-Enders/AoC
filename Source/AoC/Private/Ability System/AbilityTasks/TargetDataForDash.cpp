// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataForDash.h"

#include "AbilitySystemComponent.h"
#include "Ability System/TargetDataUnderCrosshair.h"

UTargetDataForDash* UTargetDataForDash::CreateTargetDataForDash(UGameplayAbility* OwningAbility, const float Distance)
{
	UTargetDataForDash* myObj = NewAbilityTask<UTargetDataForDash>(OwningAbility);
	myObj->DashDistance = Distance;
	
	return myObj;
}



void UTargetDataForDash::Activate()
{
	Super::Activate();

	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendDashTargetData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataForDash::AbilityTargetDataSetCallback);
		AbilitySystemComponent->CallAllReplicatedDelegatesIfSet(AbilitySpecHandle,ActivationPredictionKey);
	}

	
}

void UTargetDataForDash::AbilityTargetDataSetCallback(const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle,
	const FGameplayTag ActivationTag)
{
	
	AbilitySystemComponent->ClearAbilityReplicatedDataCache(GetAbilitySpecHandle(),Ability->GetCurrentActivationInfo());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(AbilityTargetDataHandle);
	}
}


void UTargetDataForDash::SendDashTargetData()
{

	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());
	
	const APawn* Avatar = Cast<APawn>(Ability->GetAvatarActorFromActorInfo());
	const FVector AvatarsLocation = Avatar->GetActorRightVector();
	FVector2D LastGroundVel = FVector2d( Avatar->GetLastMovementInputVector()* AvatarsLocation);
	
	
	bool bDashLeft = false;
	if(LastGroundVel.X < 0 || LastGroundVel.Y < 0)
	{
		bDashLeft = true;
	}
		
	
	const FVector AvatarLocation = Ability->GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector RightVector = Ability->GetAvatarActorFromActorInfo()->GetActorRightVector();
	FVector TargetLocation;

	if(bDashLeft)
	{
		TargetLocation = AvatarLocation + (RightVector * DashDistance * -1.f);
	}
	else
	{
		TargetLocation = AvatarLocation + (RightVector * DashDistance);
	}
	
	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_LocationInfo* TargetData_LocationInfo = new FGameplayAbilityTargetData_LocationInfo();

	TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(TargetLocation);
	GameplayAbilityTargetDataHandle.Add(TargetData_LocationInfo);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		GameplayAbilityTargetDataHandle, FGameplayTag(),
				AbilitySystemComponent->ScopedPredictionKey
				);

	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(GameplayAbilityTargetDataHandle);
	}
	
	
}
