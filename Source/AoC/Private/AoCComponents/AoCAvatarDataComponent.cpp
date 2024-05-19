// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCAvatarDataComponent.h"

#include "Ability System/AoCAbilitySystemLibrary.h"


UAoCAvatarDataComponent::UAoCAvatarDataComponent()
{
	
}

void UAoCAvatarDataComponent::InitializeAvatarData(const ECharacterClass& CharacterClass)
{
	if(UAoCAvatarDataInfo* AoCAvatarDataInfo = UAoCAbilitySystemLibrary::GetAoCAvatarDataInfo(GetOwner()))
	{
		AvatarData = AoCAvatarDataInfo->RetrieveAvatarDataInfo(CharacterClass);
	}
}


void UAoCAvatarDataComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

