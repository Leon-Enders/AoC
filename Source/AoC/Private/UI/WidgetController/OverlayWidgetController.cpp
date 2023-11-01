// Created by Leon Enders


#include "UI/WidgetController/OverlayWidgetController.h"

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
		AoCAs->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAs->GetHealthMaxAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAs->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AoCAs->GetManaMaxAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}