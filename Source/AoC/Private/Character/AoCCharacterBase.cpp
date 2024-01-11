// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemComponent.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AttackComponent = CreateDefaultSubobject<USkeletalMeshComponent>("AttackComponent");
	AttackComponent->SetupAttachment(GetMesh(),"Hand_Right_Socket");
	AttackComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	
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

	const FVector SocketLocation = AttackComponent->GetSocketLocation(AttackSocketName);
	return SocketLocation;
}

UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAoCCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
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
	if(UAoCAbilitySystemComponent* AoCAbilitySystemComponent = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent))
	{
		AoCAbilitySystemComponent->AddCharacterAbilities(StartUpAbilities);
	}
}


void AAoCCharacterBase::InitializeAttributes() const
{
	ApplyGameplayEffectToSelf(1.f, DefaultPrimaryAttributes);
	ApplyGameplayEffectToSelf(1.f, DefaultSecondaryAttributes);
	ApplyGameplayEffectToSelf(1.f, DefaultVitalAttributes);
}
