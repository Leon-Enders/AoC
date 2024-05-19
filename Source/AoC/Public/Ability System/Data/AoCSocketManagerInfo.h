// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AoCSocketManagerInfo.generated.h"




USTRUCT(BlueprintType)
struct FAoCSocketManagerData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category="SocketProperties")
	bool bHasWeapon = false;
	
	UPROPERTY(EditDefaultsOnly, Category="SocketProperties")
	FName AttackSocketName;

	UPROPERTY(EditDefaultsOnly, Category="SocketProperties")
	FName LeftHandSocketName;

	UPROPERTY(EditDefaultsOnly, Category="SocketProperties")
	FName RightHandSocketName;
};


UCLASS()
class AOC_API UAoCSocketManagerInfo : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category="SocketProperties")
	TMap<FName, FAoCSocketManagerData> SocketManagerDataByName;

	FAoCSocketManagerData RetrieveSocketManagerInfo(FName CharacterName);
};
