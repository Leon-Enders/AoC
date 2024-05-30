// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemLibrary.h"

#include "AoCAbilityTypes.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemGlobals.h"
#include "Ability System/AoCAttributeSet.h"
#include "Data/CharacterClassInfo.h"
#include "Game/AoCGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AoCPlayerState.h"
#include "UI/HUD/AoCHUD.h"
#include "UI/WidgetController/AoCWidgetController.h"
#include "AoCComponents/AoCAvatarDataComponent.h"

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


UCharacterClassInfo* UAoCAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AAoCGameModeBase* AoCGameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AoCGameMode == nullptr) return nullptr;
	return AoCGameMode->CharacterClassInfo;
}

UAoCAvatarDataInfo* UAoCAbilitySystemLibrary::GetAoCAvatarDataInfo(const UObject* WorldContextObject)
{
	const AAoCGameModeBase* AoCGameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AoCGameMode == nullptr) return nullptr;
	check(AoCGameMode->AoCAvatarDataInfo);
	return AoCGameMode->AoCAvatarDataInfo;
}

UAoCSocketManagerInfo* UAoCAbilitySystemLibrary::GetAoCSocketManagerInfo(const UObject* WorldContextObject)
{
	const AAoCGameModeBase* AoCGameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AoCGameMode == nullptr) return nullptr;
	check(AoCGameMode->AoCSocketManagerInfo);
	return AoCGameMode->AoCSocketManagerInfo;
}

UAoCTargetingInfo* UAoCAbilitySystemLibrary::GetAoCTargetingInfo(const UObject* WorldContextObject)
{
	const AAoCGameModeBase* AoCGameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AoCGameMode == nullptr) return nullptr;
	check(AoCGameMode->AoCTargetingInfo);
	return AoCGameMode->AoCTargetingInfo;
}

UAoCComboInfo* UAoCAbilitySystemLibrary::GetAoCComboInfo(const UObject* WorldContextObject)
{
	const AAoCGameModeBase* AoCGameMode = Cast<AAoCGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (AoCGameMode == nullptr) return nullptr;
	check(AoCGameMode->AoCComboInfo);
	return AoCGameMode->AoCComboInfo;
}

UAoCTargetComponent* UAoCAbilitySystemLibrary::GetTargetComponent(UObject* SourceObject)
{
	return UAoCAbilitySystemGlobals::GetAoCComponentFromSourceObject<UAoCTargetComponent>(SourceObject);
}

UAoCComboComponent* UAoCAbilitySystemLibrary::GetComboComponent(UObject* SourceObject)
{
	return UAoCAbilitySystemGlobals::GetAoCComponentFromSourceObject<UAoCComboComponent>(SourceObject);
}

UAoCAvatarDataComponent* UAoCAbilitySystemLibrary::GetAvatarDataComponent(UObject* SourceObject)
{
	return UAoCAbilitySystemGlobals::GetAoCComponentFromSourceObject<UAoCAvatarDataComponent>(SourceObject);
}

UAoCSocketManagerComponent* UAoCAbilitySystemLibrary::GetSocketManagerComponent(UObject* SourceObject)
{
	return UAoCAbilitySystemGlobals::GetAoCComponentFromSourceObject<UAoCSocketManagerComponent>(SourceObject);
}



void UAoCAbilitySystemLibrary::InitializeAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass,
                                                    float Level, UAbilitySystemComponent* AbilitySystemComponent)
{

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	
	const AActor* Avatar = AbilitySystemComponent->GetAvatarActor();
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

void UAoCAbilitySystemLibrary::GiveStartUpAbilities(const UObject* WorldContextObject,
	UAbilitySystemComponent* AbilitySystemComponent, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);

	for(const auto AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}

	for(const auto AbilityClass : CharacterClassInfo->GetClassDefaultInfo(CharacterClass).StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
		AbilitySystemComponent->GiveAbility(AbilitySpec);
	}
	
}

bool UAoCAbilitySystemLibrary::GetIsCriticalHit(const FGameplayEffectContextHandle& GameplayEffectContextHandle)
{
	
	if(const FGameplayEffectContext* EffectContext = GameplayEffectContextHandle.Get())
	{
		const FAoCGameplayEffectContext* AoCGameplayEffectContext = static_cast<const FAoCGameplayEffectContext*>(EffectContext);

		return AoCGameplayEffectContext->GetIsCriticalHit();
	}
	return false;
}

void UAoCAbilitySystemLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& GameplayEffectContextHandle, const bool IsCriticalHit)
{
	FGameplayEffectContext* EffectContext = GameplayEffectContextHandle.Get();
	FAoCGameplayEffectContext* AoCGameplayEffectContext = static_cast<FAoCGameplayEffectContext*>(EffectContext);
	AoCGameplayEffectContext->SetIsCriticalHit(IsCriticalHit);
}

void UAoCAbilitySystemLibrary::GetAllLivePlayersInRadius(const UObject* WorldContextObject,const TArray<AActor*> ActorsToIgnore, TArray<AActor*>& OutActors, float Radius, const FVector& Origin)
{

	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);
	
	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, Origin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
	}
	
	for(const auto Overlap : Overlaps)
	{
		if(AActor* OverlappedActor = Overlap.GetActor())
		{
			if(OverlappedActor->Implements<UCombatInterface>() && !ICombatInterface::Execute_GetIsDead(OverlappedActor))
			{
				OutActors.Add(OverlappedActor);
			}
		}
	}
}

bool UAoCAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	const bool bBothArePlayers = FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"));
	const bool bBothAreEnemies = FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy"));
	const bool bFriend = bBothAreEnemies || bBothArePlayers;

	return !bFriend;
}

