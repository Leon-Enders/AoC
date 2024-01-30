// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCEnemy.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/AoCAttributeSet.h"

AAoCEnemy::AAoCEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAoCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAoCAttributeSet>("Attribute Set");

	
	
}

void AAoCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	InitializeAttributes();
	InitializeHealthBar();
	
	
	
}

void AAoCEnemy::InitAbilityActorInfo()
{
	Super::InitAbilityActorInfo();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UAoCAbilitySystemComponent* AASC = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	if(AASC)
	{
		AASC->InitAoCAbilityComponent();
	}
}

int32 AAoCEnemy::GetPlayerLevel()
{
	return Level;
}

void AAoCEnemy::InitializeAttributes()
{
	UAoCAbilitySystemLibrary::InitializeAttributes(this, CharacterClass, GetPlayerLevel(),AbilitySystemComponent);
}
