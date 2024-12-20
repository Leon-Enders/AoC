// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetController/AttributeMenuWidgetController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Data/AttributeInfo.h"
#include "Ability System/AoCAttributeSet.h"
#include "AoCComponents/AoCXPComponent.h"
#include "Player/AoCPlayerState.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfos);
	
	UAoCAttributeSet* AoCAS = CastChecked<UAoCAttributeSet>(AttributeSet);
	for(const auto& pair : AoCAS->TagsToAttribute)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(pair.Value()).AddLambda(
			[this, pair](const FOnAttributeChangeData& Data)
		{
				BroadCastAttributeInfo(pair.Value(), pair.Key);
		}
		);
	}

	const AAoCPlayerState* AoCPS = CastChecked<AAoCPlayerState>(PlayerState);
	AoCPS->GetXPComponent()->OnAttributePointsChanged.AddLambda
	([this, AoCPS](int32 NewLevel)
	{
		OnAttributePointsChangeDelegate.Broadcast(AoCPS->GetXPComponent()->GetAttributePoints());
	});
}

void UAttributeMenuWidgetController::BroadCastInitialValue()
{
	check(AttributeInfos);
	
	UAoCAttributeSet* AoCAS = CastChecked<UAoCAttributeSet>(AttributeSet);

	for(const auto& pair : AoCAS->TagsToAttribute)
	{
		BroadCastAttributeInfo(pair.Value(), pair.Key);
	}
	
	const AAoCPlayerState* AoCPS = CastChecked<AAoCPlayerState>(PlayerState);
	OnAttributePointsChangeDelegate.Broadcast(AoCPS->GetXPComponent()->GetAttributePoints());
}

void UAttributeMenuWidgetController::BroadCastAttributeInfo(const FGameplayAttribute& GameplayAttribute, const FGameplayTag& AttributeTag) const
{
	FAoCAttributeInfo Info = AttributeInfos->FindAttributeInfoByTag(AttributeTag);
	Info.AttributeValue = GameplayAttribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
