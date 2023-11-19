// Copyright by Leon Enders ©, All Rights Reserved.


#include "Actor/EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Ability System/AoCAttributeSet.h"

// Sets default values
AEffectActor::AEffectActor()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>("Root");
	SetRootComponent(Root);
	
}


void AEffectActor::BeginPlay()
{
	Super::BeginPlay();


	
}



void AEffectActor::ApplyGameplayEffect(TSubclassOf<UGameplayEffect> EffectToApply, AActor* TargetActor)
{
	check(EffectToApply);
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetASC == nullptr)return;

	
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectToApply, 1.f, GameplayEffectContextHandle);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());

	const bool IsInfiniteEffect = GameplayEffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if(IsInfiniteEffect && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		ActiveHandles.Add(ActiveGameplayEffectHandle, TargetASC);
	}
			
	
	
	
	

	
}

void AEffectActor::OnOverlap(AActor* TargetActor)
{

	if(InstantEffectApplyPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffect(InstantGameplayEffect, TargetActor);
	}
	if(DurationEffectApplyPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffect(DurationGameplayEffect, TargetActor);
	}
	if(InfiniteEffectApplyPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyGameplayEffect(InfiniteGameplayEffect, TargetActor);
	}
}

void AEffectActor::EndOverlap(AActor* TargetActor)
{

	if(InstantEffectApplyPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffect(InstantGameplayEffect, TargetActor);
	}
	if(DurationEffectApplyPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffect(DurationGameplayEffect, TargetActor);
	}
	if(InfiniteEffectApplyPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyGameplayEffect(InfiniteGameplayEffect, TargetActor);
	}

	
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if(!IsValid(TargetASC))return;
		{
			
			TArray<FActiveGameplayEffectHandle> HandlesToRemove;
			
			for(auto HandlePair : ActiveHandles)
			{
				if(HandlePair.Value == TargetASC)
				{
					TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1.f);
					HandlesToRemove.Add(HandlePair.Key);
				}
				
			}

			for(auto& Handle: HandlesToRemove)
			{
				ActiveHandles.FindAndRemoveChecked(Handle);
			}
			
			
		}
	}
}



