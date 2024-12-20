// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCSocketManagerComponent.h"

#include "AoCGameplayTags.h"
#include "Data/AoCSocketManagerDataAsset.h"


UAoCSocketManagerComponent::UAoCSocketManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	MainHandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MainHandComponent");
	OffHandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("OffHandComponent");
	
}


void UAoCSocketManagerComponent::InitializeAoCComponent()
{
	if(USkeletalMeshComponent* SkeletalMeshComponent = GetOwner()->GetComponentByClass<USkeletalMeshComponent>())
	{
		OwnerMesh = SkeletalMeshComponent;
	}
		

	

	
	MainHandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(SocketManagerData->bHasMainHandWeapon)MainHandComponent->SetSkeletalMeshAsset(SocketManagerData->MainHandWeapon);
	OffHandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if(SocketManagerData->bHasOffHandWeapon)OffHandComponent->SetSkeletalMeshAsset(SocketManagerData->OffHandWeapon);
	
	MainHandComponent->AttachToComponent(OwnerMesh,FAttachmentTransformRules::SnapToTargetIncludingScale, SocketManagerData->RightHandSocketName);
	OffHandComponent->AttachToComponent(OwnerMesh,FAttachmentTransformRules::SnapToTargetIncludingScale, SocketManagerData->LeftHandSocketName);

}


FVector UAoCSocketManagerComponent::GetMainHandSocketLocation(const FGameplayTag& MontageTag)const
{
	if(!SocketManagerData->bHasMainHandWeapon)
	{
		const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
		
		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_LeftHand)
		{
			return OwnerMesh->GetSocketLocation(SocketManagerData->LeftHandSocketName);
		}

		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_RightHand)
		{

			return OwnerMesh->GetSocketLocation(SocketManagerData->RightHandSocketName);
		}
		
		return FVector();
	}
	return MainHandComponent->GetSocketLocation(SocketManagerData->MainHandWeaponSocketName);
}

FVector UAoCSocketManagerComponent::GetOffHandSocketLocation(const FGameplayTag& MontageTag)const
{
	return OwnerMesh->GetSocketLocation(SocketManagerData->LeftHandSocketName);
}

void UAoCSocketManagerComponent::HandleDeath()const
{
	if(GetOwnerRole() == ROLE_Authority && SocketManagerData->bHasMainHandWeapon)
	{
		MainHandComponent->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	}
	
	
	MainHandComponent->SetSimulatePhysics(true);
	MainHandComponent->SetEnableGravity(true);
	MainHandComponent->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
}

void UAoCSocketManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}








