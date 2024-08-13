// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "Data/UI/AoCUIAbilityDataAsset.h"


void UOverlayWidgetController::BroadCastInitialValue()
{
	const UAoCAttributeSet* AoCAs = CastChecked<UAoCAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AoCAs->GetHealth());
	OnMaxHealthChanged.Broadcast(AoCAs->GetMaxHealth());

	OnManaChanged.Broadcast(AoCAs->GetMana());
	OnMaxManaChanged.Broadcast(AoCAs->GetMaxMana());

	if(UAoCAbilitySystemComponent* AoCAbilitySystemComponent = Cast<UAoCAbilitySystemComponent>(AbilitySystemComponent))
	InitializeAbilityData(AoCAbilitySystemComponent);

	// Initialize AbilityUI DataAsset

	
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



void UOverlayWidgetController::SetUIAbilityDataAsset(UAoCUIAbilityDataAsset* AoCUIAbilityDataAsset)
{
	check(AoCUIAbilityDataAsset);
	UIAbilityDataAsset = AoCUIAbilityDataAsset;
}

void UOverlayWidgetController::InitializeAbilityData(UAoCAbilitySystemComponent* AoCAbilitySystemComponent)
{
	if(!AoCAbilitySystemComponent->bHasStartUpAbilities) return;

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
