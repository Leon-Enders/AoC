// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/CombatComponent.h"

#include "AoCGameplayTags.h"
#include "AoCComponents/ComboComponent.h"
#include "AoCComponents/TargetComponent.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
	ComboComponent = CreateDefaultSubobject<UComboComponent>("ComboComponent");
	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
	
}


void UCombatComponent::InitializeCombatComponents(UAbilitySystemComponent* AbilitySystemComponent)
{
	ComboComponent->InitializeComboComponent(AbilitySystemComponent);
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
	
}

FVector UCombatComponent::GetMainHandSocketLocation_Implementation(const FGameplayTag MontageTag)
{
return FVector();
}

FVector UCombatComponent::GetOffHandSocketLocation_Implementation(const FGameplayTag MontageTag)
{
	return ICombatInterface::GetOffHandSocketLocation_Implementation(MontageTag);
}

UAnimMontage* UCombatComponent::GetHitMontage_Implementation()
{
	return ICombatInterface::GetHitMontage_Implementation();
}

TArray<FTaggedMontages> UCombatComponent::GetTaggedMontages_Implementation()
{
	return ICombatInterface::GetTaggedMontages_Implementation();
}

bool UCombatComponent::GetIsDead_Implementation()
{
	return ICombatInterface::GetIsDead_Implementation();
}

UNiagaraSystem* UCombatComponent::GetBloodEffect_Implementation()
{
	return ICombatInterface::GetBloodEffect_Implementation();
}

void UCombatComponent::die()
{
}

UTargetComponent* UCombatComponent::GetTargetComponent_Implementation()
{
	return TargetComponent;
}

UComboComponent* UCombatComponent::GetComboComponent_Implementation()
{
	return ComboComponent;
}




