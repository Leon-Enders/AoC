// Copyright by Leon Enders ©, All Rights Reserved.


#include "Actor/EffectActor.h"

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



