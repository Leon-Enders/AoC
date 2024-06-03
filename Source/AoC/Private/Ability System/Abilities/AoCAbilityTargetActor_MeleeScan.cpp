// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCAbilityTargetActor_MeleeScan.h"

#include "AbilitySystemComponent.h"
#include "Abilities/GameplayAbility.h"

AAoCAbilityTargetActor_MeleeScan::AAoCAbilityTargetActor_MeleeScan(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PostUpdateWork;
	
	if(UAbilitySystemComponent* AbilitySystemComponent = OwningAbility->GetAbilitySystemComponentFromActorInfo())
	{
		//TODO: Add delegates to set a boolean for the tick trace for the MeleeScan Notify State start and end AbilitySystemComponent->AddGameplayEventTagContainerDelegate()
		// -->One Delegate for start one for end
		// Need to create the GameplayTags in c++ and remove them from config file
	}
}


void AAoCAbilityTargetActor_MeleeScan::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

FGameplayAbilityTargetDataHandle AAoCAbilityTargetActor_MeleeScan::MakeTargetData(
	const TArray<FHitResult>& HitResults) const
{
	if (OwningAbility)
	{
		/** Use the source location instead of the literal origin */
		return StartLocation.MakeTargetDataHandleFromHitResults(OwningAbility,HitResults);
	}

	return FGameplayAbilityTargetDataHandle();
}
