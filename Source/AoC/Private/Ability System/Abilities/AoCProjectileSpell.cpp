// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCProjectileSpell.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AoCGameplayTags.h"
#include "Actor/AoCProjectile.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UAoCProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);


	
	
}

void UAoCProjectileSpell::SpawnProjectile(const FVector& TargetLocation, const bool AB)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if(!bIsServer)
	{
		return;
	}
	
	
	if(ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()))
	{
		const APawn* Avatar = Cast<APawn>(GetAvatarActorFromActorInfo());
		FVector SocketLocation;

		if(AB)
		{
			SocketLocation = CombatInterface->GetOffHandSocketLocation();
			
		}
		else
		{
			SocketLocation = CombatInterface->GetAttackSocketLocation();
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
		const FGameplayEffectSpecHandle DamageSpecHandle = ASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(),ASC->MakeEffectContext());

		const FAoCGameplayTags AoCGameplayTags = FAoCGameplayTags::Get();
		const float DamageVal = DamageMagnitude.GetValueAtLevel(GetAbilityLevel());

		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, AoCGameplayTags.Damage, DamageVal);
		
		
		Projectile->DamageHandle = DamageSpecHandle;
		Projectile->FinishSpawning(SpawnTransform);
		
	}
}
