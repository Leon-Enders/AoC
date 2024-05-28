#include "AoCAbilityTypes.h"

#include "AoCComponents/AoCAvatarDataComponent.h"
#include "AoCComponents/AoCSocketManagerComponent.h"
#include "AoCComponents/AoCComboComponent.h"
#include "AoCComponents/AoCTargetComponent.h"

void FAoCGameplayAbilityActorInfo::InitFromActor(AActor* InOwnerActor, AActor* InAvatarActor,
                                                 UAbilitySystemComponent* InAbilitySystemComponent)
{
	Super::InitFromActor(InOwnerActor, InAvatarActor, InAbilitySystemComponent);

	//TODO: I have no clue why I this works, but it does, maybe understand it at some point
	if(InAvatarActor== NULL)return;
	AoCAvatarDataComponent = InAvatarActor->FindComponentByClass<UAoCAvatarDataComponent>();
	AoCSocketManagerComponent = InAvatarActor->FindComponentByClass<UAoCSocketManagerComponent>();
	AoCTargetComponent = InAvatarActor->FindComponentByClass<UAoCTargetComponent>();
	AoCComboComponent = InAvatarActor->FindComponentByClass<UAoCComboComponent>();
}

void FAoCGameplayAbilityActorInfo::ClearActorInfo()
{
	Super::ClearActorInfo();
	
	AoCAvatarDataComponent = nullptr;
	AoCSocketManagerComponent = nullptr;
	AoCTargetComponent = nullptr;
	AoCComboComponent = nullptr;
}

UAoCAvatarDataComponent* FAoCGameplayAbilityActorInfo::GetAvatarDataComponent() const
{
	return AoCAvatarDataComponent.IsValid() ? AoCAvatarDataComponent.Get() : nullptr;
}

UAoCSocketManagerComponent* FAoCGameplayAbilityActorInfo::GetSocketManagerComponent() const
{
	return AoCSocketManagerComponent.IsValid() ? AoCSocketManagerComponent.Get() : nullptr;
}

UAoCTargetComponent* FAoCGameplayAbilityActorInfo::GetTargetComponent() const
{
	return AoCTargetComponent.IsValid() ? AoCTargetComponent.Get() : nullptr;
}

UAoCComboComponent* FAoCGameplayAbilityActorInfo::GetComboComponent() const
{
	return AoCComboComponent.IsValid() ? AoCComboComponent.Get() : nullptr;
}



bool FAoCGameplayEffectContext::NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess)
{
	
	uint32 RepBits = 0;
	
	if (Ar.IsSaving())
	{
		if (bReplicateInstigator && Instigator.IsValid())
		{
			RepBits |= 1 << 0;
		}
		if (bReplicateEffectCauser && EffectCauser.IsValid() )
		{
			RepBits |= 1 << 1;
		}
		if (AbilityCDO.IsValid())
		{
			RepBits |= 1 << 2;
		}
		if (bReplicateSourceObject && SourceObject.IsValid())
		{
			RepBits |= 1 << 3;
		}
		if (Actors.Num() > 0)
		{
			RepBits |= 1 << 4;
		}
		if (HitResult.IsValid())
		{
			RepBits |= 1 << 5;
		}
		if (bHasWorldOrigin)
		{
			RepBits |= 1 << 6;
		}
		if(bIsCriticalHit)
		{
			RepBits |= 1 << 7;
		}
	}

	Ar.SerializeBits(&RepBits, 8);

	if (RepBits & (1 << 0))
	{
		Ar << Instigator;
	}
	if (RepBits & (1 << 1))
	{
		Ar << EffectCauser;
	}
	if (RepBits & (1 << 2))
	{
		Ar << AbilityCDO;
	}
	if (RepBits & (1 << 3))
	{
		Ar << SourceObject;
	}
	if (RepBits & (1 << 4))
	{
		SafeNetSerializeTArray_Default<31>(Ar, Actors);
	}
	if (RepBits & (1 << 5))
	{
		if (Ar.IsLoading())
		{
			if (!HitResult.IsValid())
			{
				HitResult = TSharedPtr<FHitResult>(new FHitResult());
			}
		}
		HitResult->NetSerialize(Ar, Map, bOutSuccess);
	}
	if (RepBits & (1 << 6))
	{
		Ar << WorldOrigin;
		bHasWorldOrigin = true;
	}
	else
	{
		bHasWorldOrigin = false;
	}
	if(RepBits & (1 << 7))
	{
		Ar << bIsCriticalHit;
	}

	if (Ar.IsLoading())
	{
		AddInstigator(Instigator.Get(), EffectCauser.Get()); // Just to initialize InstigatorAbilitySystemComponent
	}	
	
	bOutSuccess = true;
	return true;
}
