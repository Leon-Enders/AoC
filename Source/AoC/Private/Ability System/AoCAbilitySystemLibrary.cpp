// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/AoCAbilitySystemLibrary.h"

#include "AoCAbilityTypes.h"
#include "Ability System/AoCAbilitySystemComponent.h"
#include "Ability System/AoCAbilitySystemGlobals.h"
#include "Ability System/AoCAttributeSet.h"
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
			if(IsValid(OverlappedActor) && OverlappedActor->Implements<UAbilitySystemInterface>())
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

