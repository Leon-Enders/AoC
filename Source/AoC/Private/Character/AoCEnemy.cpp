// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCEnemy.h"

#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/AoCAttributeSet.h"
#include "AI/AoCAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
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
	AoCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsRangedAttacker?"), CharacterClass == ECharacterClass::E_Caster);
	
}

void AAoCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	if(HasAuthority())
	{
		UAoCAbilitySystemLibrary::GiveStartUpAbilities(this, AbilitySystemComponent, CharacterClass);
	}
	InitializeAoCComponents();
	
	AbilitySystemComponent->RegisterGameplayTagEvent(FAoCGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved).AddUObject(
			this,
			&AAoCEnemy::HitReactTagChanged
		);
	
}


void AAoCEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UAoCAbilitySystemComponent* AASC = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	
	if(AASC)
	{
		AASC->InitAoCAbilityComponent();
	}

	if(HasAuthority())
	{
		InitializeAttributes();
	}
}



void AAoCEnemy::InitializeAttributes() const 
{
	UAoCAbilitySystemLibrary::InitializeAttributes(this, CharacterClass, Level,AbilitySystemComponent);
}



void AAoCEnemy::die()
{
	Super::die();
	if(AoCAIController) AoCAIController->GetBlackboardComponent()->SetValueAsBool(FName("IsDead?"),true);
}

int32 AAoCEnemy::GetPlayerLevel_Implementation() const
{
	return Level;
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

void AAoCEnemy::InitializeAoCComponents() const
{
	Super::InitializeAoCComponents();
}
