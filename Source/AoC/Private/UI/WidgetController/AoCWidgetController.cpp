// Created by Leon Enders


#include "UI/WidgetController/AoCWidgetController.h"
#include "Ability System/AoCAttributeSet.h"


void UAoCWidgetController::InitWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PC;
	PlayerState = WidgetControllerParams.PS;
	AttributeSet = WidgetControllerParams.AS;
	AbilitySystemComponent = WidgetControllerParams.ASC;
}

void UAoCWidgetController::BroadcastInitialValues()
{
	if(UAoCAttributeSet* AoCAttributeSet = Cast<UAoCAttributeSet>(AttributeSet))
	{
		OnHealthChangedSignature.Broadcast(AoCAttributeSet->GetHealth());
		OnMaxHealthChangedSignature.Broadcast(AoCAttributeSet->GetHealthMax());
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AoCAttributeSet->GetHealthAttribute()).AddUObject(this, &UAoCWidgetController::HealthChange);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
			AoCAttributeSet->GetHealthMaxAttribute()).AddUObject(this, &UAoCWidgetController::MaxHealthChange);
	}
}



void UAoCWidgetController::HealthChange(const FOnAttributeChangeData& Data)
{
	
		OnHealthChangedSignature.Broadcast(Data.NewValue);
	
}

void UAoCWidgetController::MaxHealthChange(const FOnAttributeChangeData& Data)
{
	
		OnMaxHealthChangedSignature.Broadcast(Data.NewValue);
	
}


