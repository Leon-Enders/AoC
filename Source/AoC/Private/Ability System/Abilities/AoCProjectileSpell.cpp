// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCProjectileSpell.h"

#include "Actor/AoCProjectile.h"
#include "Interaction/CombatInterface.h"

void UAoCProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	const bool bIsServer = HasAuthority(&ActivationInfo);

	if(!bIsServer)
	{
		return;
	}
	
}

void UAoCProjectileSpell::SpawnProjectile(const FVector& TargetLocation)
{
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		const FRotator Rotation = (TargetLocation-SocketLocation).Rotation();
		FTransform SpawnTransform;
		
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rotation.Quaternion());
		
		AAoCProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAoCProjectile>(ProjectileClass,
			SpawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		//TODO: Apply Effect to do damage
		Projectile->FinishSpawning(SpawnTransform);
		
	}
}
