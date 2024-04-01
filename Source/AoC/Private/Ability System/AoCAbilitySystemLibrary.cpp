// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemLibrary.h"

#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAttributeSet.h"
#include "Ability System/Data/CharacterClassInfo.h"
#include "Game/AoCGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "UI/WidgetController/AoCWidgetController.h"

UAttributeMenuWidgetController* UAoCAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AAoCHUD* HUD = Cast<AAoCHUD>(PC->GetHUD()))
		{
			AAoCPlayerState* PS = PC->GetPlayerState<AAoCPlayerState>();
			UAoCAbilitySystemComponent* ASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAoCAttributeSet* AS = Cast<UAoCAttributeSet>(PS->GetAttributeSet());

			
			const FWidgetControllerParams WidgetControllerParams(PC, PS, AS, ASC);
			return HUD->GetAttributeMenuWidgetController(WidgetControllerParams);
		}
		
		
	}
	
	return nullptr;
}

UOverlayWidgetController* UAoCAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	
	if(APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if(AAoCHUD* HUD = Cast<AAoCHUD>(PC->GetHUD()))
		{
			AAoCPlayerState* PS = PC->GetPlayerState<AAoCPlayerState>();
			UAoCAbilitySystemComponent* ASC = Cast<UAoCAbilitySystemComponent>(PS->GetAbilitySystemComponent());
			UAoCAttributeSet* AS = Cast<UAoCAttributeSet>(PS->GetAttributeSet());

			
			const FWidgetControllerParams WidgetControllerParams(PC, PS, AS, ASC);
			return HUD->GetOverlayWidgetController(WidgetControllerParams);
		}
		
		
	}
	
	return nullptr;
}

void UAoCAbilitySystemLibrary::InitializeAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass,
	float Level, UAbilitySystemComponent* AbilitySystemComponent)
{

	const AAoCGameModeBase* GameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(GameMode == nullptr)
	{
		return;
	}
	
	const AActor* Avatar = AbilitySystemComponent->GetAvatarActor();
	UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;
	const FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	
	FGameplayEffectContextHandle PrimaryEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	PrimaryEffectContextHandle.AddSourceObject(Avatar);
	
	const FGameplayEffectSpecHandle GameplayEffectPrimarySpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes,Level,PrimaryEffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectPrimarySpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	SecondaryEffectContextHandle.AddSourceObject(Avatar);
	
	const FGameplayEffectSpecHandle GameplayEffectSecondarySpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->SecondaryAttributes,Level,SecondaryEffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectSecondarySpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalEffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	VitalEffectContextHandle.AddSourceObject(Avatar);
	
	const FGameplayEffectSpecHandle GameplayEffectVitalSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes,Level,VitalEffectContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*GameplayEffectVitalSpecHandle.Data.Get());

	
	
}

void UAoCAbilitySystemLibrary::InitializeCommonAbilities(const UObject* WorldContextObject,
	UAbilitySystemComponent* AbilitySystemComponent)
{
	const AAoCGameModeBase* GameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if(GameMode == nullptr)
	{
		return;
	}

	
	UCharacterClassInfo* CharacterClassInfo = GameMode->CharacterClassInfo;

	for(const auto AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
}

