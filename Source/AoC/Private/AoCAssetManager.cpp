// Copyright by Leon Enders ©, All Rights Reserved.


#include "AoCAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "AoCGameplayTags.h"


UAoCAssetManager& UAoCAssetManager::Get()
{
	check(GEngine);

	UAoCAssetManager* AoCAssetManager = Cast<UAoCAssetManager>(GEngine->AssetManager.Get());
	
	return *AoCAssetManager;
}

void UAoCAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAoCGameplayTags::Get().InitializeNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitTargetDataScriptStructCache();
}
