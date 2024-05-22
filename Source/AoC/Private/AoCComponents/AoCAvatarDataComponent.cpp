// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCAvatarDataComponent.h"

#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Net/UnrealNetwork.h"


UAoCAvatarDataComponent::UAoCAvatarDataComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UAoCAvatarDataComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UAoCAvatarDataComponent,AvatarData,COND_None);
}

void UAoCAvatarDataComponent::InitializeAoCComponent(FName CharacterName)
{
	if(UAoCAvatarDataInfo* AoCAvatarDataInfo = UAoCAbilitySystemLibrary::GetAoCAvatarDataInfo(GetOwner()))
	{
		AvatarData = AoCAvatarDataInfo->RetrieveAvatarData(CharacterName);
	}
}


UAnimMontage* UAoCAvatarDataComponent::GetHitMontage() const
{
	check(AvatarData.HitReactMontage);
	return AvatarData.HitReactMontage;
}

UAnimMontage* UAoCAvatarDataComponent::GetDeathMontage() const
{
	check(AvatarData.DeathMontage);
	return AvatarData.DeathMontage;
}

UNiagaraSystem* UAoCAvatarDataComponent::GetBloodEffect() const
{
	check(AvatarData.BloodEffect);
	return AvatarData.BloodEffect;
}

TArray<FGameplayTagMontage> UAoCAvatarDataComponent::GetGameplayTagMontages() const
{
	return AvatarData.GameplayTagMontages;
}

float UAoCAvatarDataComponent::GetAvatarLifeSpan() const
{
	return AvatarData.LifeSpan;
}


