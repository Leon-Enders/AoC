// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AoCGameModeBase.generated.h"


class UAoCTargetingInfo;
class UAoCSocketManagerInfo;
class UAoCAvatarDataInfo;
class UCharacterClassInfo;
/**
 * 
 */
UCLASS()
class AOC_API AAoCGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category="AoCDataInfo")
	TObjectPtr<UCharacterClassInfo> CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category="AoCDataInfo")
	TObjectPtr<UAoCAvatarDataInfo> AoCAvatarDataInfo;

	UPROPERTY(EditDefaultsOnly, Category="AoCDataInfo")
	TObjectPtr<UAoCSocketManagerInfo> AoCSocketManagerInfo;

	UPROPERTY(EditDefaultsOnly, Category="AoCDataInfo")
	TObjectPtr<UAoCTargetingInfo> AoCTargetingInfo;

};
