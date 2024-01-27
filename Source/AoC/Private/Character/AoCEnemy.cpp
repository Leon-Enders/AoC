// Copyright by Leon Enders ©, All Rights Reserved.


#include "Character/AoCEnemy.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "Components/WidgetComponent.h"
#include "UI/UserWidget/AoCUserWidget.h"

AAoCEnemy::AAoCEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAoCAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<UAoCAttributeSet>("Attribute Set");

	HealthBarWidget = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidget");
	HealthBarWidget->SetupAttachment(RootComponent);
	
}

void AAoCEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilityActorInfo();
	InitializeAttributes();


	const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);

	if(UAoCUserWidget* AoCHealthBar = Cast<UAoCUserWidget>(HealthBarWidget->GetWidget()))
	{
		AoCHealthBar->SetWidgetController(this);
	}
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAs->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAs->GetHealthMaxAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
	);
	
	OnHealthChanged.Broadcast(AoCAs->GetHealth());
	OnMaxHealthChanged.Broadcast(AoCAs->GetHealthMax());

	
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
