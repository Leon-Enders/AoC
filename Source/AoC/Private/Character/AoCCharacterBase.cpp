// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"


#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoC/AoC.h"
#include "AoCComponents/AoCAvatarDataComponent.h"
#include "AoCComponents/AoCSocketManagerComponent.h"
#include "AoCComponents/TargetComponent.h"
#include "Components/CapsuleComponent.h"
#include "AoCComponents/AoCComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/WidgetComponent/FloatingBarComponent.h"
#include "MotionWarpingComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;

	SetupAoCComponents();
	SetupCharacterComponents();
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
	
	//SetLifeSpan(AvatarDataComponent->GetAvatarLifeSpan());
	MultiCastHandleDeath();
	
}




void AAoCCharacterBase::MultiCastHandleDeath_Implementation()
{
	
	HealthBarComponent->SetHiddenInGame(true);
	if(IsPlayerControlled())
	{
		GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
		GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldStatic,ECR_Block);
		//PlayAnimMontage(AvatarDataComponent->GetDeathMontage());
		GetCharacterMovement()->DisableMovement();
	}
	else
	{
		//SocketManagerComponent->HandleDeath();
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
	for(const auto AoCComponent : AoCComponents)
	{
		AoCComponent->InitializeAoCComponent(CharacterName);
	}
}


void AAoCCharacterBase::InitAbilityActorInfo()
{
}

int32 AAoCCharacterBase::GetPlayerLevel() const
{
	return 0;
}


void AAoCCharacterBase::SetupCharacterComponents()
{
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

void AAoCCharacterBase::SetupAoCComponents()
{
	AoCComponents.Add(CreateDefaultSubobject<UAoCAvatarDataComponent>("AvatarDataComponent"));
	AoCComponents.Add(CreateDefaultSubobject<UTargetComponent>("TargetComponent"));
	AoCComponents.Add(CreateDefaultSubobject<UAoCSocketManagerComponent>("SocketManagerComponent"));
}