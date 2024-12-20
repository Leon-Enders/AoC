// Copyright by Leon Enders ©, All Rights Reserved.


#include "UI/WidgetComponent/FloatingBarComponent.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "UI/UserWidget/AoCUserWidget.h"

UFloatingBarComponent::UFloatingBarComponent()
{
	
}

void UFloatingBarComponent::InitializeFloatingBar(UAoCAttributeSet* AttributeSet,
	UAoCAbilitySystemComponent* AbilitySystemComponent)
{
	OwnerAttributeSet = AttributeSet;
	OwnerAbilitySystemComponent = AbilitySystemComponent;

	InitWidget();
	BindDelegates();
}

void UFloatingBarComponent::BindDelegates()
{
	
	UAoCUserWidget* AoCHealthBar = Cast<UAoCUserWidget>(GetUserWidgetObject());
	check(AoCHealthBar);
	
	// Fires Of Blueprint event that binds events to the attribute change delegates
	AoCHealthBar->SetWidgetController(this);
	
	


	// Bind Lambdas to Attribute Change Delegates
	OwnerAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	OwnerAttributeSet->GetHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		OnHealthChanged.Broadcast(Data.NewValue);
	}
	);
	OwnerAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
	OwnerAttributeSet->GetMaxHealthAttribute()).AddLambda(
	[this](const FOnAttributeChangeData& Data)
	{
		if(GetOwner() && GetOwner()->HasAuthority())
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
		else
		{
			OnMaxHealthChanged.Broadcast(OwnerAttributeSet->GetMaxHealth());
		}
	
	});

	// Broadcast first values
	OnHealthChanged.Broadcast(OwnerAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(OwnerAttributeSet->GetMaxHealth());
}
