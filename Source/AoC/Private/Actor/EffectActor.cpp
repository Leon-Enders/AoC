// Copyright by Leon Enders ©, All Rights Reserved.


#include "Actor/EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
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

void AEffectActor::ApplyGameplayEffect(const TSubclassOf<UGameplayEffect> EffectToApply, AActor* TargetActor)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(EffectToApply);
	if(TargetASC == nullptr)return;

	
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetASC->MakeEffectContext();
	GameplayEffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle GameplayEffectSpecHandle = TargetASC->MakeOutgoingSpec(EffectToApply, 1.f, GameplayEffectContextHandle);
	TargetASC->ApplyGameplayEffectSpecToSelf(*GameplayEffectSpecHandle.Data.Get());
	
}





