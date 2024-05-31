// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"


#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoC/AoC.h"
#include "AoCComponents/AoCAvatarDataComponent.h"
#include "AoCComponents/AoCSocketManagerComponent.h"
#include "Components/CapsuleComponent.h"
#include "AoCComponents/AoCComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/WidgetComponent/FloatingBarComponent.h"
#include "MotionWarpingComponent.h"
#include "AoCComponents/AoCTargetComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	
	SetupCharacterComponents();
	SetupAoCComponents();
}

void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(TargetOutlineMaterial))
	{
		
		GetMesh()->SetOverlayMaterial(TargetOutlineMaterial);
		GetMesh()->SetOverlayMaterialMaxDrawDistance(1.f);
	}
	if(IsPlayerControlled())
	{
		HealthBarComponent->SetHiddenInGame(true);
	}
}


void AAoCCharacterBase::die()
{
	if(bIsDead) return;
	bIsDead = true;


	const float LifeSpan = AvatarDataComponent->GetAvatarLifeSpan();
	SetLifeSpan(LifeSpan);
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


UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAoCComponent* AAoCCharacterBase::GetAoCComponent(TSubclassOf<UAoCComponent> AoCComponentClass) const
{
	return AoCComponentsMap.FindRef(AoCComponentClass);
}


void AAoCCharacterBase::InitializeAttributes() const
{
}

void AAoCCharacterBase::InitializeAoCComponents() const
{
	
	HealthBarComponent->InitializeFloatingBar(Cast<UAoCAttributeSet>(AttributeSet), Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent));

	for(const auto& AoCComponent : AoCComponentsMap)
	{
		AoCComponent.Value->InitializeAoCComponent();
	}
}

void AAoCCharacterBase::OnTargetSet(bool bIsTargeted)
{
	if(bIsTargeted)
	{
		GetMesh()->SetOverlayMaterialMaxDrawDistance(0.f);
	}
	else
	{
		GetMesh()->SetOverlayMaterialMaxDrawDistance(1.f);
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
	AvatarDataComponent = CreateDefaultSubobject<UAoCAvatarDataComponent>("AvatarDataComponent");
	AoCComponentsMap.Add(UAoCAvatarDataComponent::StaticClass(), AvatarDataComponent);
	SocketManagerComponent = CreateDefaultSubobject<UAoCSocketManagerComponent>("SocketManagerComponent");
	AoCComponentsMap.Add(UAoCSocketManagerComponent::StaticClass(), SocketManagerComponent);
	TargetComponent = CreateDefaultSubobject<UAoCTargetComponent>("TargetComponent");
	AoCComponentsMap.Add(UAoCTargetComponent::StaticClass(), TargetComponent);
}