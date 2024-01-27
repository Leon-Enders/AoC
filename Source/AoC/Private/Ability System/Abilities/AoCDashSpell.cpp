// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/Abilities/AoCDashSpell.h"



void UAoCDashSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
	
}

void UAoCDashSpell::SpawnParticle(const FVector& TargetLocation)
{
	
	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	FRotator Rotation = (TargetLocation-AvatarLocation).Rotation();

	FTransform Transform;
	Transform.SetLocation(AvatarLocation);
	Transform.SetRotation(Rotation.Quaternion());
	auto effectActor=GetWorld()->SpawnActorDeferred<AActor>(DashEffect,
			Transform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
	effectActor->FinishSpawning(Transform);
}






