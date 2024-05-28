#pragma once
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "AoCAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAoCGameplayAbilityActorInfo : public FGameplayAbilityActorInfo
{
	GENERATED_USTRUCT_BODY()
     
		typedef Super FGameplayAbilityActorInfo;
     
	virtual ~FAoCGameplayAbilityActorInfo()
	{
	}
	
	
	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<class UAoCAvatarDataComponent> AoCAvatarDataComponent;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<class UAoCSocketManagerComponent> AoCSocketManagerComponent;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<class UAoCTargetComponent> AoCTargetComponent;

	UPROPERTY(BlueprintReadOnly, Category = "ActorInfo")
	TWeakObjectPtr<class UAoCComboComponent> AoCComboComponent;
 
	virtual void InitFromActor(AActor* OwnerActor, AActor* AvatarActor, UAbilitySystemComponent* InAbilitySystemComponent) override;
	virtual void ClearActorInfo() override;
	
	class UAoCAvatarDataComponent* GetAvatarDataComponent() const;
	class UAoCSocketManagerComponent* GetSocketManagerComponent() const;
	class UAoCTargetComponent* GetTargetComponent() const;
	class UAoCComboComponent* GetComboComponent() const;
};



USTRUCT(BlueprintType)
struct FAoCGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()


public:
	/*Getter and Setters*/
	bool GetIsCriticalHit()const  {return bIsCriticalHit;}
	void SetIsCriticalHit(bool IsCriticalHit){bIsCriticalHit = IsCriticalHit;}


	/*Overrides*/
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