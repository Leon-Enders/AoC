// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemGlobals.h"
#include "AoCAbilityTypes.h"
#include "Interaction/AoCComponentInterface.h"

FGameplayEffectContext* UAoCAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAoCGameplayEffectContext();
}

FGameplayAbilityActorInfo* UAoCAbilitySystemGlobals::AllocAbilityActorInfo() const
{
	return new FAoCGameplayAbilityActorInfo();
}

template <typename T>
T* UAoCAbilitySystemGlobals::GetAoCComponentFromActor(const AActor* Actor)
{
	if (Actor == nullptr)
	{
		return nullptr;
	}
	
	const IAoCComponentInterface* ACI = Cast<IAoCComponentInterface>(Actor);
	if (ACI)
	{
		return Cast<T>(ACI->GetAoCComponent(T::StaticClass()));
	}

	return nullptr;
}