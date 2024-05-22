// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"

#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoC/AoC.h"
#include "AoCComponents/AoCAvatarDataComponent.h"
#include "AoCComponents/AoCSocketManagerComponent.h"
#include "AoCComponents/TargetComponent.h"
#include "Components/CapsuleComponent.h"
#include "AoCComponents/ComboComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/WidgetComponent/FloatingBarComponent.h"
#include "MotionWarpingComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	AvatarDataComponent = CreateDefaultSubobject<UAoCAvatarDataComponent>("AvatarDataComponent");
	SocketManagerComponent = CreateDefaultSubobject<UAoCSocketManagerComponent>("SocketManagerComponent");
	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
	ComboComponent = CreateDefaultSubobject<UComboComponent>("ComboComponent");
	HealthBarComponent = CreateDefaultSubobject<UFloatingBarComponent>("HealthBar");
	HealthBarComponent->SetupAttachment(GetRootComponent());
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//We have to Overlap Capsule for now since its a modular character
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//no need to overlap with mesh yet
	//GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	
}

void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsPlayerControlled())
	{
		HealthBarComponent->SetHiddenInGame(true);
	}
	
}

void AAoCCharacterBase::die()
{
	if(bIsDead) return;
	bIsDead = true;
	
	SetLifeSpan(AvatarDataComponent->GetAvatarLifeSpan());
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
		SocketManagerComponent->HandleDeath();
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


FVector AAoCCharacterBase::GetMainHandSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	return SocketManagerComponent->GetMainHandSocketLocation(MontageTag);
}

FVector AAoCCharacterBase::GetOffHandSocketLocation_Implementation(const FGameplayTag& MontageTag)
{
	return SocketManagerComponent->GetOffHandSocketLocation(MontageTag);
}

bool AAoCCharacterBase::GetIsTargeting_Implementation() const
{
	return TargetComponent->GetIsTargeting();
}

AActor* AAoCCharacterBase::GetTarget_Implementation()
{
	return TargetComponent->GetTarget();
}


void AAoCCharacterBase::SetTarget_Implementation(AActor* TargetToSet)
{
	TargetComponent->SetTarget(TargetToSet);
}

void AAoCCharacterBase::UpdateWarpTargetName_Implementation(FName WarpTargetName)
{
	TargetComponent->UpdateWarpTargetName(WarpTargetName);
}


void AAoCCharacterBase::FindTarget_Implementation()
{
	return TargetComponent->FindTarget();
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


UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void AAoCCharacterBase::InitializeAttributes() const
{
}

void AAoCCharacterBase::InitializeAoCComponents() const
{
	HealthBarComponent->InitializeFloatingBar(Cast<UAoCAttributeSet>(AttributeSet), Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent));
	AvatarDataComponent->InitializeAvatarData(CharacterName);
	SocketManagerComponent->InitializeSocketManagerData(CharacterName,GetMesh());
	TargetComponent->InitializeTargetComponent(CharacterName, MotionWarpingComponent);
}

void AAoCCharacterBase::InitAbilityActorInfo()
{
}

