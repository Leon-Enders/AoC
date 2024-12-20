// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AoCAssetManager.generated.h"

/**
 * Asset Manager Singleton Class
 */
UCLASS()
class AOC_API UAoCAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static UAoCAssetManager& Get();
	

protected:
	virtual void StartInitialLoading() override;
};
