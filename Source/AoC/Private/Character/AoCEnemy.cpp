// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCEnemy.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/AoCAttributeSet.h"
#include "AI/AoCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

AAoCEnemy::AAoCEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAoCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAoCAttributeSet>("Attribute Set");

	
	
}

void AAoCEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AoCAIController = Cast<AAoCAIController>(NewController);
	
	AoCAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->GetBlackboardAsset());
	AoCAIController->RunBehaviorTree(BehaviorTree);
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
	Super::InitializeAttributes();
	UAoCAbilitySystemLibrary::InitializeAttributes(this, CharacterClass, GetPlayerLevel(),AbilitySystemComponent);
}
