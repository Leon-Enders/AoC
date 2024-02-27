// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataForCharacterLaunch.h"

#include "AbilitySystemComponent.h"
#include "Ability System/AbilityTasks/TargetDataForDash.h"

UTargetDataForCharacterLaunch* UTargetDataForCharacterLaunch::CreateTargetDataForLaunch(UGameplayAbility* OwningAbility,
                                                                                        const float LaunchScale)
{
	UTargetDataForCharacterLaunch* myObj = NewAbilityTask<UTargetDataForCharacterLaunch>(OwningAbility);
	myObj->LaunchScale = LaunchScale;
	return myObj;
}



void UTargetDataForCharacterLaunch::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();

	if(bIsLocallyControlled)
	{
		SendLaunchTargetData();
	}
	else
	{
		FGameplayAbilitySpecHandle AbilitySpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(AbilitySpecHandle, ActivationPredictionKey).AddUObject(this, &UTargetDataForCharacterLaunch::AbilityTargetDataSetCallback);
		AbilitySystemComponent->CallAllReplicatedDelegatesIfSet(AbilitySpecHandle,ActivationPredictionKey);
	}
}

void UTargetDataForCharacterLaunch::AbilityTargetDataSetCallback(
	const FGameplayAbilityTargetDataHandle& AbilityTargetDataHandle, const FGameplayTag ActivationTag)
{
	AbilitySystemComponent->ClearAbilityReplicatedDataCache(GetAbilitySpecHandle(),Ability->GetCurrentActivationInfo());
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(AbilityTargetDataHandle, LRDirection, FWDirection);
	}
}


void UTargetDataForCharacterLaunch::SendLaunchTargetData()
{
	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());

	LaunchScale = FMath::Max(0.01f, LaunchScale);


	AActor* AvatarActor = Ability->GetAvatarActorFromActorInfo();
	const APawn* Avatar = Cast<APawn>(AvatarActor);
	const FVector RightVector = AvatarActor->GetActorRightVector();
	const FVector ForwardVector = AvatarActor->GetActorForwardVector();
	
	const float RLDotProduct = FVector::DotProduct(Avatar->GetLastMovementInputVector(), RightVector);
	const float FBDotProduct = FVector::DotProduct(Avatar->GetLastMovementInputVector(), ForwardVector);

	if(FMath::IsNearlyEqual(RLDotProduct, 1.f,0.01))
	{
		LRDirection = E_Right;
		
	}
	else if(FMath::IsNearlyEqual(RLDotProduct, -1.f,0.01))
	{
		LRDirection = E_Left;
	}
	else
	{
		LRDirection = E_None;
	}
	
	if(FMath::IsNearlyEqual(FBDotProduct, 1.f,0.01))
	{
		FWDirection = E_Forward;
		
	}
	else if(FMath::IsNearlyEqual(FBDotProduct, -1.f,0.01))
	{
		FWDirection = E_Back;
	}
	else
	{
		FWDirection = E_None;
	}

	
	FVector XVelocity;
	FVector YVelocity;


	switch (LRDirection)
	{
	case EInputDirection::E_Left :
		XVelocity = RightVector * 500.f * -1.f;
		break;
	case EInputDirection::E_Right:
		XVelocity = RightVector * 500.f;
		break;
	default:
		break;
	}

	switch (FWDirection)
	{
	case EInputDirection::E_Forward :
		YVelocity = ForwardVector * 500.f;
		break;
	case EInputDirection::E_Back:
		YVelocity = ForwardVector * 500.f * -1.f;
		break;
	default:
		break;
	}


	const FVector EndVelocity = XVelocity * (LaunchScale/1.25f) + YVelocity * (LaunchScale/1.25f) + FVector(0.f,0.f,500.f * LaunchScale);

	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_LocationInfo* TargetData_LocationInfo = new FGameplayAbilityTargetData_LocationInfo();
	TargetData_LocationInfo->SourceLocation.LiteralTransform.SetLocation(AvatarActor->GetActorLocation());
	TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndVelocity);
	GameplayAbilityTargetDataHandle.Add(TargetData_LocationInfo);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		GameplayAbilityTargetDataHandle, FGameplayTag(),
				AbilitySystemComponent->ScopedPredictionKey
				);

	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(GameplayAbilityTargetDataHandle, LRDirection, FWDirection);
	}


	
}