// Copyright by Leon Enders ©, All Rights Reserved.


#include "Actor/AoCProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AoC/AoC.h"

// Sets default values
AAoCProjectile::AAoCProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(SphereComponent);
	bReplicates = true;

	SphereComponent->SetCollisionObjectType(ECC_Projectile);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComponent->InitialSpeed = 550.f;
	ProjectileMovementComponent->MaxSpeed = 550.f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	
}


void AAoCProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	SetLifeSpan(LifeTime);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAoCProjectile::OnSphereOverlap);
	
}

void AAoCProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	if(!DamageHandle.Data.IsValid() || DamageHandle.Data->GetEffectContext().GetEffectCauser() == OtherActor) return;
	if(DamageHandle.Data->GetEffectContext().GetEffectCauser()->ActorHasTag("Enemy") && OtherActor->ActorHasTag("Enemy")) return;
	
	if(HasAuthority())
	{
		if(UAbilitySystemComponent* TargetAsc = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			TargetAsc->ApplyGameplayEffectSpecToSelf(*DamageHandle.Data.Get());
		}
	}
	
	if(!bHit)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this,ExplosionEffect,GetActorLocation());
		bHit = true;
	}
	if(HasAuthority())
	{
		Destroy();
	}
	else
	{
		bHit = true;
	}
	
}

void AAoCProjectile::Destroyed()
{
	

	if(!HasAuthority() && !bHit)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation());
		bHit = true;
	}
	Super::Destroyed();
}



