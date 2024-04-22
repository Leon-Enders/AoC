#pragma once
#include "GameplayEffectTypes.h"
#include "AoCAbilityTypes.generated.h"



USTRUCT(BlueprintType)
struct FAoCGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()


public:
	bool GetIsCriticalHit()const  {return bIsCriticalHit;}

	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual FAoCGameplayEffectContext* Duplicate() const override
	{
		FAoCGameplayEffectContext* NewContext = new FAoCGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			// Does a deep copy of the hit result
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	
	virtual bool NetSerialize(FArchive& Ar, UPackageMap* Map, bool& bOutSuccess) override;
	
	
protected:
	bool bIsCriticalHit = false;
	

	
};


template<>
struct TStructOpsTypeTraits< FAoCGameplayEffectContext > : public TStructOpsTypeTraitsBase2< FAoCGameplayEffectContext >
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true		// Necessary so that TSharedPtr<FHitResult> Data is copied around
	};
};