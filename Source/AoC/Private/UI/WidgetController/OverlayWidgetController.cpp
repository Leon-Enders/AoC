// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoCComponents/AoCXPComponent.h"
#include "Data/AoCPawnData.h"
#include "Data/UI/AoCUIAbilityDataAsset.h"
#include "Player/AoCPlayerState.h"
#include "Data/AoCAbilitySet.h"


void UOverlayWidgetController::BroadCastInitialValue()
{
	const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AoCAs->GetHealth());
	OnMaxHealthChanged.Broadcast(AoCAs->GetMaxHealth());

	OnManaChanged.Broadcast(AoCAs->GetMana());
	OnMaxManaChanged.Broadcast(AoCAs->GetMaxMana());

	OnXPRatioChanged.Broadcast(0.f);
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAoCAttributeSet* AoCAS = CastChecked<UAoCAttributeSet>(AttributeSet);
	
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAS->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAS->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChanged.Broadcast(Data.NewValue);
	}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	AoCAS->GetManaAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnManaChanged.Broadcast(Data.NewValue);
	}
	);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAS->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
		);

	if(UAoCAbilitySystemComponent* AoCAbilitySystemComponent = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent))
	{
		AoCAbilitySystemComponent->EffectDelegate.AddLambda(
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
		});
	}

	const AAoCPlayerState* AoCPS = CastChecked<AAoCPlayerState>(PlayerState);
	
	AoCPS->GetXPComponent()->OnXPChanged.AddLambda
		([this, AoCPS](int32 NewXP)
		{
			OnXPRatioChanged.Broadcast(AoCPS->GetXPComponent()->GetXPRatio());
		});
	
	AoCPS->GetXPComponent()->OnLevelChanged.AddLambda
	([this](int32 NewLevel)
	{
		OnLevelChanged.Broadcast(NewLevel);
	});
	
}


void UOverlayWidgetController::InitializeAbilityData()
{
	const AAoCPlayerState* AoCPS = CastChecked<AAoCPlayerState>(PlayerState);
	for(const auto& Pair : AoCPS->GetPawnData()->AbilitySets[0]->UIAbilityData->AbilityTagUIAbilitiesMap)
	{
		UIAbilityDataDelegate.Broadcast(Pair.Value);
	}
}
