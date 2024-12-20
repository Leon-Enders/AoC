// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCEnemy.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AI/AoCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Data/AoCAbilitySet.h"
#include "GameFramework/CharacterMovementComponent.h"

AAoCEnemy::AAoCEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAoCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAoCAttributeSet>("Attribute Set");
	
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	
}

void AAoCEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!HasAuthority()) return;
	AoCAIController = Cast<AAoCAIController>(NewController);
	
	AoCAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	AoCAIController->RunBehaviorTree(BehaviorTree);

	AoCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsHitReacting?"), false);
	AoCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsRangedAttacker?"), EnemyClass == EEnemyClass::E_Caster);
	
}

void AAoCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	InitializeAoCComponents();
	
	AbilitySystemComponent->RegisterGameplayTagEvent(FAoCGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AAoCEnemy::HitReactTagChanged
		);
	
}


void AAoCEnemy::InitAbilityActorInfo()
{
	check(AbilitySet);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UAoCAbilitySystemComponent* AASC = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	
	// Make sure to call this after setting AttributeSet
	BindAbilitySystemDelegates();
	if(AASC)
	{
		AASC->InitAoCAbilityComponent();
		AbilitySet->GiveToAbilitySystem(AASC,nullptr, AASC->GetAvatarActor(), Level);
	}
}

void AAoCEnemy::OnAvatarDeath(AActor* Killer)
{
	Super::OnAvatarDeath(Killer);
	if(AoCAIController) AoCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead?"),true);

	
	//TODO: Grant XP-Reward - temp workaround until enemies are more complex
	if(UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Killer))
	{
		FGameplayEffectContextHandle ContextHandle =  AbilitySystemComponent->MakeEffectContext();
		ContextHandle.AddSourceObject(this);
		const FGameplayEffectSpecHandle EffectHandle = AbilitySystemComponent->MakeOutgoingSpec(XPRewardEffect, Level, ContextHandle);
		
		AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*EffectHandle.Data.Get(), TargetASC);
	}
	
}


void AAoCEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bIsHitReacting ? 0.f : BaseWalkSpeed;
	if (AoCAIController && AoCAIController->GetBlackboardComponent())
	{
		AoCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsHitReacting?"), bIsHitReacting);
	}
}
