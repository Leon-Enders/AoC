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
T* UAoCAbilitySystemGlobals::GetAoCComponentFromSourceObject(const UObject* SourceObject)
{
	if (SourceObject == nullptr)
	{
		return nullptr;
	}
	
	const IAoCComponentInterface* ACI = Cast<IAoCComponentInterface>(SourceObject);
	if (ACI)
	{
		return Cast<T>(ACI->GetAoCComponent(T::StaticClass()));
	}

	return nullptr;
}