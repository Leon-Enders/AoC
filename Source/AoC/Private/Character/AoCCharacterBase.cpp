// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"
#include "AoC/AoC.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoCComponents/TargetComponent.h"
#include "Components/CapsuleComponent.h"
#include "AoCComponents/CombatComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/UserWidget/AoCUserWidget.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	bReplicates = true;
	PrimaryActorTick.bCanEverTick = false;
	MainHandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("AttackComponent");
	MainHandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//TODO:: Update OffhandComponent Logic
	OffhandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("OffhandComponent");
	OffhandComponent->SetupAttachment(GetMesh(),"Weapon_LSocket");
	OffhandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
	CombatComponent = CreateDefaultSubobject<UCombatComponent>("CombatComponent");
	
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//We have to Overlap Capsule for now since its a modular character
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	//no need to overlap with mesh yet
	//GetMesh()->SetCollisionResponseToChannel(ECC_Projectile, ECR_Overlap);

	
	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());
	
	
}

void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocallyControlled())
	{
		HealthBar->SetHiddenInGame(true);
	}
	
	MainHandComponent->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale, "Weapon_RSocket");
}

void AAoCCharacterBase::InitAbilityActorInfo()
{
}


FVector AAoCCharacterBase::GetMainHandSocketLocation()
{
	check(MainHandComponent);
	if(!bHasWeapon)
	{
		return MainHandComponent->GetComponentLocation();
	}
	return MainHandComponent->GetSocketLocation(AttackSocketName);
	
}

FVector AAoCCharacterBase::GetOffHandSocketLocation()
{
	// TODO: Properly implement OffhandSocket
	check(OffhandComponent);
	
	return GetMesh()->GetSocketLocation("Weapon_LSocket");
}

void AAoCCharacterBase::die()
{
	SetLifeSpan(LifeSpan);
	
	if(bHasWeapon)
	{
		MainHandComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	MultiCastHandleDeath();
	
}

UCombatComponent* AAoCCharacterBase::GetCombatComponent_Implementation()
{
	if(CombatComponent)
	{
		return CombatComponent;
	}
	return nullptr;
}


void AAoCCharacterBase::MultiCastHandleDeath_Implementation()
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

UAnimMontage* AAoCCharacterBase::GetHitMontage_Implementation()
{
	if(HitReactMontage)
	{
		return HitReactMontage;
	}
	return nullptr;
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




void AAoCCharacterBase::InitializeHealthBar()
{
		const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);

		HealthBar->InitWidget();
		if(UAoCUserWidget* AoCHealthBar = Cast<UAoCUserWidget>(HealthBar->GetUserWidgetObject()))
		{
			AoCHealthBar->SetWidgetController(this);
		}
	
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAs->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAs->GetMaxHealthAttribute()).AddLambda(
		[this, AoCAs](const FOnAttributeChangeData& Data)
		{
			
			if(HasAuthority())
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
			else
			{
				OnMaxHealthChanged.Broadcast(AoCAs->GetMaxHealth());
			}
	
		});
	
		OnHealthChanged.Broadcast(AoCAs->GetHealth());
		OnMaxHealthChanged.Broadcast(AoCAs->GetMaxHealth());
	
}

void AAoCCharacterBase::InitializeAttributes() const
{
	
}