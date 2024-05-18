// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "Components/ActorComponent.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/CombatSystemInterface.h"
#include "CombatComponent.generated.h"

class AAoCCharacterBase;
class UAbilitySystemComponent;
class UTargetComponent;
class UComboComponent;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UCombatComponent : public UActorComponent, public ICombatInterface
{
	GENERATED_BODY()

public:	
	UCombatComponent();
	void InitializeCombatComponents(UAbilitySystemComponent* AbilitySystemComponent);

	
	ECharacterClass GetCharacterClass()const {return CharacterClass;}
	bool GetIsDead()const {return bIsDead;}
	
protected:

	virtual void BeginPlay() override;

	//Combat Interface Overrides
	virtual FVector GetMainHandSocketLocation_Implementation(const FGameplayTag MontageTag) override;
	virtual FVector GetOffHandSocketLocation_Implementation(const FGameplayTag MontageTag) override;
	virtual UAnimMontage* GetHitMontage_Implementation() override;
	virtual TArray<FTaggedMontages> GetTaggedMontages_Implementation() override;
	virtual bool GetIsDead_Implementation() override;
	virtual UNiagaraSystem* GetBloodEffect_Implementation() override;
	virtual void die() override;
	virtual float GetDashDistanceForTag(const FGameplayTag& ComboTag) override;

	
	virtual UTargetComponent* GetTargetComponent_Implementation() override;
	virtual UComboComponent* GetComboComponent_Implementation() override;

	


	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UComboComponent> ComboComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UTargetComponent> TargetComponent;


	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	TArray<FTaggedMontages> TaggedMontages;

	// Handle Scene Properties
	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> MainHandComponent;

	UPROPERTY(EditAnywhere, Category="Combat")
	TObjectPtr<USkeletalMeshComponent> OffhandComponent;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	bool bHasWeapon = false;
	
	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	FName AttackSocketName;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	FName LeftHandSocketName;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	FName RightHandSocketName;


	// Avatar Properties
	UPROPERTY(EditDefaultsOnly, Category="AvatarProperties")
	ECharacterClass CharacterClass = ECharacterClass::E_Bruiser;

	UPROPERTY(EditAnywhere, Category="AvatarProperties")
	TObjectPtr<UAnimMontage> HitReactMontage;

	UPROPERTY(EditAnywhere,Category="AvatarProperties")
	TObjectPtr<UAnimMontage> DeathMontage;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="AvatarProperties")
	float LifeSpan = 5.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UNiagaraSystem* BloodEffect;


	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TObjectPtr<UMeleeComboInfo>MeleeComboInfo;
	
	

private:
	
	TObjectPtr<AAoCCharacterBase> OwningAvatar;
	
	bool bIsDead = false;
};

