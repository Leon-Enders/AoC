// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"
#include "Actor/AoCProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AoCComponents/AoCSocketManagerComponent.h"
#include "AoCComponents/AoCTargetComponent.h"

void UAoCProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	
	
}

void UAoCProjectileSpell::SpawnProjectile(const FVector& TargetLocation, const bool SpawnOffHand)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if(!bIsServer)
	{
		return;
	}
		
	FVector SocketLocation;
	if(SpawnOffHand)
	{
		SocketLocation = GetSocketManagerComponentFromInfo()->GetOffHandSocketLocation(FGameplayTag());
		
	}
	else
	{
		SocketLocation = GetSocketManagerComponentFromInfo()->GetMainHandSocketLocation(FAoCGameplayTags::Get().Event_Montage_Enemy_Attack_RightHand);
	}
	
	const FVector SpawnLocation = SocketLocation;
	const FRotator Rotation = (TargetLocation-SpawnLocation).Rotation();
	FTransform SpawnTransform;
	
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());
	
	AAoCProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAoCProjectile>(ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	


	
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(Projectile);
	TArray<TWeakObjectPtr<AActor>> Actors;
	Actors.Add(Projectile);
	EffectContextHandle.AddActors(Actors);
	FHitResult HitResult;
	HitResult.Location = TargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
	

	const FGameplayEffectSpecHandle DamageSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(),EffectContextHandle);
	
	const FAoCGameplayTags AoCGameplayTags = FAoCGameplayTags::Get();
	const float DamageVal = DamageMagnitude.GetValueAtLevel(GetAbilityLevel());
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, AoCGameplayTags.Damage, DamageVal);
	Projectile->DamageHandle = DamageSpecHandle;
	
	if(bIsHomingProjectile)
	{
		auto ProjectileMovementComponent = Projectile->ProjectileMovementComponent;
		ProjectileMovementComponent->bIsHomingProjectile = true;
		ProjectileMovementComponent->HomingTargetComponent = GetTargetComponentFromInfo()->GetTarget()->GetRootComponent();
	}
		
	Projectile->FinishSpawning(SpawnTransform);
			
	
}
