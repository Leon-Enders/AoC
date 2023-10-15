// Created by Leon Enders


#include "Character/AoCCharacterBase.h"

// Sets default values
AAoCCharacterBase::AAoCCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAoCCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAoCCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UAbilitySystemComponent* AAoCCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AAoCCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}


