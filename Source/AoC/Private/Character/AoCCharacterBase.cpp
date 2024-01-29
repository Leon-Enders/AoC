// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoC/AoC.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "UI/UserWidget/AoCUserWidget.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	AttackComponent = CreateDefaultSubobject<USkeletalMeshComponent>("AttackComponent");
	AttackComponent->SetupAttachment(GetMesh(),"Weapon_RSocket");
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

void AAoCCharacterBase::OnHealthChangedCallback(const FOnAttributeChangeData& Data) const
{
	
		OnHealthChanged.Broadcast(Data.NewValue);
	
	
}

void AAoCCharacterBase::OnMaxHealthChangedCallback(const FOnAttributeChangeData& Data) const
{
	
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	
	
}


void AAoCCharacterBase::InitializeAttributes()
{
	
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
	AoCAs->GetHealthAttribute()).AddUObject(this, &AAoCCharacterBase::OnHealthChangedCallback);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAs->GetHealthMaxAttribute()).AddUObject(this, &AAoCCharacterBase::OnMaxHealthChangedCallback);
	
	
	OnHealthChanged.Broadcast(AoCAs->GetHealth());
	OnMaxHealthChanged.Broadcast(AoCAs->GetHealthMax());

	


}
