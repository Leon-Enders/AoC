// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"


void UOverlayWidgetController::BroadCastInitialValue()
{
	const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AoCAs->GetHealth());
	OnMaxHealthChanged.Broadcast(AoCAs->GetHealthMax());

	OnManaChanged.Broadcast(AoCAs->GetMana());
	OnMaxManaChanged.Broadcast(AoCAs->GetManaMax());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);
	
	
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

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAs->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAs->GetManaMaxAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
		);

	UAoCAbilitySystemComponent* AoCASC = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent);
	if(AoCASC)
	{
		AoCASC->GameplayTagsAppliedDelegate.AddDynamic(this, &UOverlayWidgetController::FindRowByTag);
	}
}

void UOverlayWidgetController::FindRowByTag(const FGameplayEffectSpec& GameplayEffectSpec)
{
	FGameplayTagContainer ActiveTags;
	GameplayEffectSpec.GetAllGrantedTags(ActiveTags);

	for(auto Tag : ActiveTags)
	{
		
		auto messagerow = UIMessageDt->FindRow<FGameplayTagUIRow>(Tag.GetTagName(),FString());

		OnGameplayTagApplied.Broadcast(*messagerow);
		
	}
	
}