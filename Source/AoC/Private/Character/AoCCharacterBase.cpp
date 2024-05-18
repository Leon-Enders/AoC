// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"

#include "AoC/AoC.h"
#include "Components/CapsuleComponent.h"
#include "AoCComponents/CombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/WidgetComponent/FloatingBarComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//We have to Overlap Capsule for now since its a modular character
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//no need to overlap with mesh yet
	//GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);

	
	HealthBarComponent = CreateDefaultSubobject<UFloatingBarComponent>("HealthBar");
	HealthBarComponent->SetupAttachment(GetRootComponent());
	
}




void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsPlayerControlled())
	{
		HealthBarComponent->SetHiddenInGame(true);
	}
}

void AAoCCharacterBase::InitAbilityActorInfo()
{
}

//
//
void AAoCCharacterBase::MultiCastHandleDeath_Implementation()
{
	HealthBarComponent->SetHiddenInGame(true);
	if(IsPlayerControlled())
	{
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
		//check(DeathMontage);
		//PlayAnimMontage(DeathMontage);
		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		//MainHandComponent->SetSimulatePhysics(true);
		//MainHandComponent->SetEnableGravity(true);
		//MainHandComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetEnableGravity(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

		GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

//UAnimMontage* AAoCCharacterBase::GetHitMontage_Implementation()
//{
//	if(HitReactMontage)
//	{
//		return HitReactMontage;
//	}
//	return nullptr;
//}
//
//TArray<FTaggedMontages> AAoCCharacterBase::GetTaggedMontages_Implementation()
//{
//	return TaggedMontages;
//}
//
//bool AAoCCharacterBase::GetIsDead_Implementation()
//{
//	return bIsDead;
//}
//
//UNiagaraSystem* AAoCCharacterBase::GetBloodEffect_Implementation()
//{
//	return BloodEffect;
//}
//
UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UCombatComponent* AAoCCharacterBase::GetCombatComponent() const
{
	check(CombatComponent);
	return CombatComponent;
}


void AAoCCharacterBase::InitializeAttributes() const
{
}

void AAoCCharacterBase::InitializeAoCComponents() const
{
}
