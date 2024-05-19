// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCComponents/AoCSocketManagerComponent.h"

#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemLibrary.h"


UAoCSocketManagerComponent::UAoCSocketManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAoCSocketManagerComponent::InitializeSocketManagerData(FName CharacterName, USkeletalMeshComponent* Mesh)
{
	if(IsValid(Mesh))
	OwnerMesh = Mesh;
	
	if(UAoCSocketManagerInfo* AoCSocketManagerInfo = UAoCAbilitySystemLibrary::GetAoCSocketManagerInfo(GetOwner()))
	{
		SocketManagerData = AoCSocketManagerInfo->RetrieveSocketManagerData(CharacterName);
	}

	
	SocketManagerData.MainHandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("MainHandComponent");
	SocketManagerData.MainHandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SocketManagerData.OffHandComponent = CreateDefaultSubobject<USkeletalMeshComponent>("OffHandComponent");
	SocketManagerData.OffHandComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

FVector UAoCSocketManagerComponent::GetMainHandSocketLocation(const FGameplayTag MontageTag)const
{
	if(!SocketManagerData.bHasWeapon)
	{
		const FAoCGameplayTags& AoCGameplayTags = FAoCGameplayTags::Get();
		
		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_LeftHand)
		{
			return OwnerMesh->GetSocketLocation(SocketManagerData.LeftHandSocketName);
		}

		if(MontageTag == AoCGameplayTags.Event_Montage_Enemy_Attack_RightHand)
		{

			return OwnerMesh->GetSocketLocation(SocketManagerData.RightHandSocketName);
		}
		
		return FVector();
	}
	return SocketManagerData.MainHandComponent->GetSocketLocation(SocketManagerData.MainHandWeaponSocketName);
}

FVector UAoCSocketManagerComponent::GetOffHandSocketLocation(const FGameplayTag MontageTag)const
{
	return OwnerMesh->GetSocketLocation(SocketManagerData.LeftHandSocketName);
}

void UAoCSocketManagerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	SocketManagerData.MainHandComponent->AttachToComponent(OwnerMesh,FAttachmentTransformRules::SnapToTargetIncludingScale, SocketManagerData.RightHandSocketName);
	SocketManagerData.OffHandComponent->AttachToComponent(OwnerMesh,FAttachmentTransformRules::SnapToTargetIncludingScale, SocketManagerData.LeftHandSocketName);
}








