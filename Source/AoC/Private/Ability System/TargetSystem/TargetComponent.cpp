// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/TargetSystem/TargetComponent.h"


UTargetComponent::UTargetComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	
}



void UTargetComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}



void UTargetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}

