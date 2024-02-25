// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"


void UOverlayWidgetController::BroadCastInitialValue()
{
	const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AoCAs->GetHealth());
	OnMaxHealthChanged.Broadcast(AoCAs->GetMaxHealth());

	OnManaChanged.Broadcast(AoCAs->GetMana());
	OnMaxManaChanged.Broadcast(AoCAs->GetMaxMana());
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
	AoCAs->GetMaxHealthAttribute()).AddLambda(
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
		AoCAs->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
		);

	Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent)->EffectDelegate.AddLambda(
	[this](const FGameplayTagContainer& AssetTags)
	{
		for(const auto Tag : AssetTags)
		{
		
			auto MessageTag = FGameplayTag::RequestGameplayTag("Message");
			if(Tag.MatchesTag(MessageTag))
			{
				const FGameplayTagUIRow* Row = GetDataTableRowByTag<FGameplayTagUIRow>(MessageWidgetDataTable, Tag);
				WidgetMessageDelegate.Broadcast(*Row);
			}
			
		
		}
		
	}
	);
	
		
	
}
