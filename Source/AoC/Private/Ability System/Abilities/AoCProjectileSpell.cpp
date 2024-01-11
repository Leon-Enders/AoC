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

	if(bIsServer)
	{
		if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(ActorInfo->AvatarActor))
		{
			const FVector SpawnLocation = CombatInterface->GetCombatSocketLocation();
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);

			AAoCProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAoCProjectile>(AoCProjectile,
				SpawnTransform,
				GetOwningActorFromActorInfo(),
				Cast<APawn>(GetOwningActorFromActorInfo()),
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

			if(Projectile)
			{
				Projectile->FinishSpawning(SpawnTransform);
			}
		}
		
	}
	
}
