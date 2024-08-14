// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
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
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAoCAttributeSet* AoCAS = CastChecked<UAoCAttributeSet>(AttributeSet);
	const AAoCPlayerState* AoCPS = CastChecked<AAoCPlayerState>(PlayerState);
	
	UIAbilityDataAsset = AoCPS->GetPawnData()->AbilitySets[0]->UIAbilityData;
	
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

		if(AoCAbilitySystemComponent->bHasStartUpAbilities)
		{
			InitializeAbilityData(AoCAbilitySystemComponent);
		}
		else
		{
			AoCAbilitySystemComponent->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::InitializeAbilityData);
			
		}
		
	}
}


void UOverlayWidgetController::InitializeAbilityData(UAoCAbilitySystemComponent* AoCAbilitySystemComponent)
{
	if(!AoCAbilitySystemComponent->bHasStartUpAbilities) return;
	if(!UIAbilityDataAsset) return;
	
	FForEachAbilitySignature ForEachAbilityDelegate;


	ForEachAbilityDelegate.BindLambda(
		[this, AoCAbilitySystemComponent](const FGameplayAbilitySpec& AbilitySpec)
		{
			FAoCUIAbilityData UIAbilityData = UIAbilityDataAsset->FindAoCUIAbilityDataForTag(AoCAbilitySystemComponent->GetAbilityTagBySpec(AbilitySpec));
			UIAbilityData.InputTag = AoCAbilitySystemComponent->GetInputTagBySpec(AbilitySpec);
			UIAbilityDataDelegate.Broadcast(UIAbilityData);
		});

	AoCAbilitySystemComponent->ExecuteForEachAbility(ForEachAbilityDelegate);
}
