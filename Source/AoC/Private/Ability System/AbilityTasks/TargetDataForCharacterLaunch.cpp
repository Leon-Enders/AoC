// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataForCharacterLaunch.h"

#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"
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
		ValidData.Broadcast(AbilityTargetDataHandle, ActivationTag);
	}
}

void UTargetDataForCharacterLaunch::SendLaunchTargetData()
{
	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());


	const FVector EndVelocity = CalculateDashData();

	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_LocationInfo* TargetData_LocationInfo = new FGameplayAbilityTargetData_LocationInfo();
	TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndVelocity);
	GameplayAbilityTargetDataHandle.Add(TargetData_LocationInfo);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		GameplayAbilityTargetDataHandle, AnimationTag,
				AbilitySystemComponent->ScopedPredictionKey
				);

	
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(GameplayAbilityTargetDataHandle, AnimationTag);
	}


	
}

const FVector UTargetDataForCharacterLaunch::CalculateDashData()
{
	LaunchScale = FMath::Max(0.01f, LaunchScale);
	const FAoCGameplayTags& GameplayTags = FAoCGameplayTags::Get();
	
	AActor* AvatarActor = Ability->GetAvatarActorFromActorInfo();
	const APawn* Avatar = Cast<APawn>(AvatarActor);
	const FVector RightVector = AvatarActor->GetActorRightVector();
	const FVector ForwardVector = AvatarActor->GetActorForwardVector();
	
	const float RLDotProduct = FVector::DotProduct(Avatar->GetLastMovementInputVector(), RightVector);
	const float FBDotProduct = FVector::DotProduct(Avatar->GetLastMovementInputVector(), ForwardVector);
	FVector XVelocity = FVector(0.f,0.f,0.f);
	FVector YVelocity= FVector(0.f,0.f,0.f);


	
	if(FMath::IsNearlyEqual(RLDotProduct, 1.f,0.01))
	{
		XVelocity = RightVector * 500.f;
		AnimationTag = GameplayTags.Animations_Right;
		
	}
	else if(FMath::IsNearlyEqual(RLDotProduct, -1.f,0.01))
	{
		XVelocity = RightVector * 500.f * -1.f;
		AnimationTag = GameplayTags.Animations_Left;
	}
	else
	{
		AnimationTag = GameplayTags.Animations_Idle;
	}
	
	if(FMath::IsNearlyEqual(FBDotProduct, 1.f,0.01))
	{
		YVelocity = ForwardVector * 500.f;
		AnimationTag = GameplayTags.Animations_Forward;
		
	}
	else if(FMath::IsNearlyEqual(FBDotProduct, -1.f,0.01))
	{
		YVelocity = ForwardVector * 500.f * -1.f;
		AnimationTag = GameplayTags.Animations_Backward;
	}
	

	return XVelocity * (LaunchScale/1.25f) + YVelocity * (LaunchScale/1.25f) + FVector(0.f,0.f,500.f * LaunchScale);

}

