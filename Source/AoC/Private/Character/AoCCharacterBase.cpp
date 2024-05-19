// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"

#include "AoCGameplayTags.h"
#include "AoC/AoC.h"
#include "AoCComponents/AoCAvatarDataComponent.h"
#include "AoCComponents/TargetComponent.h"
#include "Components/CapsuleComponent.h"
#include "AoCComponents/ComboComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/WidgetComponent/FloatingBarComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	AvatarDataComponent = CreateDefaultSubobject<UAoCAvatarDataComponent>("AvatarDataComponent");

	
	MainHandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("AttackComponent");
	MainHandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//TODO:: Update OffhandComponent Logic
	OffhandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("OffhandComponent");
	OffhandComponent->SetupAttachment(GetMesh(),"Weapon_LSocket");
	OffhandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
	ComboComponent = CreateDefaultSubobject<UComboComponent>("ComboComponent");
	
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
	AvatarDataComponent->InitializeAvatarData(CharacterClass);
	MainHandComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_RSocket");
}

void AAoCCharacterBase::InitAbilityActorInfo()
{
}


FVector AAoCCharacterBase::GetMainHandSocketLocation_Implementation(const FGameplayTag MontageTag)
{
	check(MainHandComponent);
	if(!bHasWeapon)
	{
		const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
		
		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_LeftHand)
		{
			return GetMesh()->GetSocketLocation(LeftHandSocketName);
		}

		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_RightHand)
		{
			return GetMesh()->GetSocketLocation(RightHandSocketName);
		}
		
		return FVector();
	}
	return MainHandComponent->GetSocketLocation(AttackSocketName);
	
}

FVector AAoCCharacterBase::GetOffHandSocketLocation_Implementation(const FGameplayTag GameplayTag)
{
	// TODO: Properly implement OffhandSocket
	check(OffhandComponent);
	
	return GetMesh()->GetSocketLocation("Weapon_LSocket");
}

void AAoCCharacterBase::die()
{
	if(bIsDead) return;
	bIsDead = true;
	
	SetLifeSpan(AvatarDataComponent->GetAvatarLifeSpan());
	
	if(bHasWeapon)
	{
		MainHandComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	MultiCastHandleDeath();
	
}



void AAoCCharacterBase::MultiCastHandleDeath_Implementation()
{
	HealthBarComponent->SetHiddenInGame(true);
	if(IsPlayerControlled())
	{
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
		PlayAnimMontage(AvatarDataComponent->GetDeathMontage());
		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		MainHandComponent->SetSimulatePhysics(true);
		MainHandComponent->SetEnableGravity(true);
		MainHandComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->SetEnableGravity(true);
		GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);

		GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


bool AAoCCharacterBase::GetIsDead_Implementation()
{
	return bIsDead;
}


UAnimMontage* AAoCCharacterBase::GetHitMontage_Implementation()
{
	return AvatarDataComponent->GetHitMontage();
}

UAnimMontage* AAoCCharacterBase::GetDeathMontage_Implementation()
{
	return AvatarDataComponent->GetDeathMontage();
}

TArray<FGameplayTagMontage> AAoCCharacterBase::GetGameplayMontages_Implementation()
{
	return AvatarDataComponent->GetGameplayTagMontages();
}


UNiagaraSystem* AAoCCharacterBase::GetBloodEffect_Implementation()
{
	return AvatarDataComponent->GetBloodEffect();
}


UTargetComponent* AAoCCharacterBase::GetTargetComponent_Implementation()
{
	if(!TargetComponent) return nullptr;
	return TargetComponent;
}


UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAoCCharacterBase::InitializeAttributes() const
{
}

void AAoCCharacterBase::InitializeAoCComponents() const
{
}
