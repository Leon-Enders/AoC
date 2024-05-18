// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/CombatComponent.h"

#include "AoCGameplayTags.h"
#include "AoCComponents/ComboComponent.h"
#include "AoCComponents/TargetComponent.h"
#include "Character/AoCCharacterBase.h"


UCombatComponent::UCombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	
	ComboComponent = CreateDefaultSubobject<UComboComponent>("ComboComponent");
	TargetComponent = CreateDefaultSubobject<UTargetComponent>("TargetComponent");
	
}

void UCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	OwningAvatar = Cast<AAoCCharacterBase>(GetOwner());
	
}

void UCombatComponent::InitializeCombatComponents(UAbilitySystemComponent* AbilitySystemComponent)
{
	ComboComponent->InitializeComboComponent(AbilitySystemComponent);
}




FVector UCombatComponent::GetMainHandSocketLocation_Implementation(const FGameplayTag MontageTag)
{
	check(MainHandComponent);
	if(!bHasWeapon)
	{
		const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
		
		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_LeftHand)
		{
			return OwningAvatar->GetMesh()->GetSocketLocation(LeftHandSocketName);
		}

		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_RightHand)
		{
			return OwningAvatar->GetMesh()->GetSocketLocation(RightHandSocketName);
		}
		
		return FVector();
	}
	return MainHandComponent->GetSocketLocation(AttackSocketName);
}

FVector UCombatComponent::GetOffHandSocketLocation_Implementation(const FGameplayTag MontageTag)
{
	check(OffhandComponent);
	
	return OwningAvatar->GetMesh()->GetSocketLocation("Weapon_LSocket");
}

UAnimMontage* UCombatComponent::GetHitMontage_Implementation()
{
	if(HitReactMontage)
	{
		return HitReactMontage;
	}
	return nullptr;
}

TArray<FTaggedMontages> UCombatComponent::GetTaggedMontages_Implementation()
{
	return TaggedMontages;
}

bool UCombatComponent::GetIsDead_Implementation()
{
	return bIsDead;
}

UNiagaraSystem* UCombatComponent::GetBloodEffect_Implementation()
{
	return ICombatInterface::GetBloodEffect_Implementation();
}

void UCombatComponent::die()
{
	if(bIsDead) return;
	bIsDead = true;
	
	OwningAvatar->SetLifeSpan(LifeSpan);
	
	if(bHasWeapon)
	{
		MainHandComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}

	// Broadcast die event to owning avatar
	OwningAvatar->OnDieDelegate.Broadcast();
}

float UCombatComponent::GetDashDistanceForTag(const FGameplayTag& ComboTag)
{
	return MeleeComboInfo->GetAttackDistanceForTag(ComboTag);
}

UTargetComponent* UCombatComponent::GetTargetComponent_Implementation()
{
	return TargetComponent;
}

UComboComponent* UCombatComponent::GetComboComponent_Implementation()
{
	return ComboComponent;
}






