// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTasks/TargetDataForDash.h"

#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"


UTargetDataForDash* UTargetDataForDash::CreateTargetDataForDash(UGameplayAbility* OwningAbility,const float Distance)
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
		ValidData.Broadcast(AbilityTargetDataHandle, ActivationTag);
	}
}




void UTargetDataForDash::SendDashTargetData()
{

	FScopedPredictionWindow PredictionWindow = FScopedPredictionWindow(AbilitySystemComponent.Get());

	
	const FVector EndLocation = CalculateDashData();
	
	FGameplayAbilityTargetDataHandle GameplayAbilityTargetDataHandle;
	FGameplayAbilityTargetData_LocationInfo* TargetData_LocationInfo = new FGameplayAbilityTargetData_LocationInfo();

	TargetData_LocationInfo->TargetLocation.LiteralTransform.SetLocation(EndLocation);
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


const FVector UTargetDataForDash::CalculateDashData()
{
	AActor* AvatarActor = Ability->GetAvatarActorFromActorInfo();
	const APawn* Avatar = Cast<APawn>(AvatarActor);
	const FVector RightVector = AvatarActor->GetActorRightVector();
	const FVector ForwardVector = AvatarActor->GetActorForwardVector();
	
	const float RLDotProduct = FVector::DotProduct(Avatar->GetLastMovementInputVector(), RightVector);
	const float FBDotProduct = FVector::DotProduct(Avatar->GetLastMovementInputVector(), ForwardVector);

	const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
	FVector RightLocation = FVector(0.f,0.f,0.f);
	FVector FowardLocation = FVector(0.f,0.f,0.f);



	//TODO create a virtual function with AnimationTag as reference to set it by this logic
	bool bIsForward = false;
	if(FMath::IsNearlyEqual(RLDotProduct, 1.f,0.01))
	{
		RightLocation = RightVector * DashDistance;
		AnimationTag = AoCGameplayTags.Animations_Right;
		
	}
	else if(FMath::IsNearlyEqual(RLDotProduct, -1.f,0.01))
	{
		
		RightLocation = RightVector * DashDistance * -1.f;
		AnimationTag = AoCGameplayTags.Animations_Left;
	}
	else
	{
		AnimationTag = AoCGameplayTags.Animations_Idle;
	}
	
	if(FMath::IsNearlyEqual(FBDotProduct, 1.f,0.01))
	{
		FowardLocation = ForwardVector * DashDistance/2.f;
		AnimationTag = AoCGameplayTags.Animations_Forward;
		bIsForward = true;
		
	}
	else if(FMath::IsNearlyEqual(FBDotProduct, -1.f,0.01))
	{
		FowardLocation = ForwardVector * DashDistance/2.f * -1.f;
		AnimationTag = AoCGameplayTags.Animations_Backward;
		bIsForward = true;
	}
	

	if(bIsForward)
	{
		return AvatarActor->GetActorLocation() + FowardLocation;
	}
	return AvatarActor->GetActorLocation() + FowardLocation + RightLocation;
	
	
}


