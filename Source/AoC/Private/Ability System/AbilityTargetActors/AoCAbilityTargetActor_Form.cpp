// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Form.h"

#include "Abilities/GameplayAbility.h"
#include "Ability System/Abilities/AoCChampionMeleeAbility.h"

AAoCAbilityTargetActor_Form::AAoCAbilityTargetActor_Form(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	ShouldProduceTargetDataOnServer = true;
}

void AAoCAbilityTargetActor_Form::StartTargeting(UGameplayAbility* InAbility)
{
	Super::StartTargeting(InAbility);
	SourceActor = InAbility->GetCurrentActorInfo()->AvatarActor.Get();
}

void AAoCAbilityTargetActor_Form::SendTargetDataBacktoServer(const FGameplayAbilityTargetDataHandle& InData,
	FGameplayTag ApplicationTag)
{
	if(bHasDataBeenSentToServer)
	{
		return;
	}
	
	if(UAoCChampionMeleeAbility* LocalAbility = Cast<UAoCChampionMeleeAbility>(OwningAbility))
	{
		LocalAbility->OnTargetDataReadyCallback(InData, ApplicationTag);
		bHasDataBeenSentToServer = true;
	}
}


TArray<FOverlapResult> AAoCAbilityTargetActor_Form::GetPotentialTargets(const FVector& Origin,
                                                                        float SphereRadius)
{
	bool bTraceComplex = false;
	
	FCollisionQueryParams Params(SCENE_QUERY_STAT(RadiusTargetingOverlap), bTraceComplex);
	Params.bReturnPhysicalMaterial = false;
	
	TArray<FOverlapResult> OverlapResults;

	SourceActor->GetWorld()->OverlapMultiByObjectType(OverlapResults, Origin, FQuat::Identity, FCollisionObjectQueryParams(ECC_Pawn), FCollisionShape::MakeSphere(SphereRadius), Params);


	return OverlapResults;
}

FGameplayAbilityTargetDataHandle AAoCAbilityTargetActor_Form::MakeTargetData(
	const TArray<TWeakObjectPtr<AActor>>& Actors, const FVector& Origin) const
{
	if (OwningAbility)
	{
		/** Use the source location instead of the literal origin */
		return StartLocation.MakeTargetDataHandleFromActors(Actors, false);
	}

	return FGameplayAbilityTargetDataHandle();
}
