// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "AoC/AoC.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	AttackComponent = CreateDefaultSubobject<USkeletalMeshComponent>("AttackComponent");
	AttackComponent->SetupAttachment(GetMesh(),"Weapon_RSocket");
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	
	
}

void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAoCCharacterBase::InitAbilityActorInfo()
{
}

FVector AAoCCharacterBase::GetCombatSocketLocation()
{
	check(AttackComponent);
	if(!bHasWeapon)
	{
		return AttackComponent->GetComponentLocation();
	}
	return AttackComponent->GetSocketLocation(AttackSocketName);
	
}

UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAoCCharacterBase::ApplyGameplayEffectToSelf(float Level, TSubclassOf<UGameplayEffect> GameplayEffectToApply) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectToApply);
	
	FGameplayEffectContextHandle EffectContext = GetAbilitySystemComponent()->MakeEffectContext();
	EffectContext.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle EffectSpec = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectToApply, Level, EffectContext);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpec.Data.Get(), GetAbilitySystemComponent());

	
}

void AAoCCharacterBase::AddCharacterAbilities() 
{
	if(!HasAuthority())
	{
		return;
	}
	
	UAoCAbilitySystemComponent* AoCAbilitySystemComponent = CastChecked<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	AoCAbilitySystemComponent->AddCharacterAbilities(StartUpAbilities);
	
}


void AAoCCharacterBase::InitializeAttributes() const
{
	ApplyGameplayEffectToSelf(1.f, DefaultPrimaryAttributes);
	ApplyGameplayEffectToSelf(1.f, DefaultSecondaryAttributes);
	ApplyGameplayEffectToSelf(1.f, DefaultVitalAttributes);
}
