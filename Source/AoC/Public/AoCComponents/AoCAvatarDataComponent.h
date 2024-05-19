// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Data/AoCAvatarDataInfo.h"
#include "Components/ActorComponent.h"
#include "AoCAvatarDataComponent.generated.h"


enum class ECharacterClass : uint8;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCAvatarDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAoCAvatarDataComponent();
	void InitializeAvatarData(const ECharacterClass& CharacterClass);
	
protected:
	
	virtual void BeginPlay() override;

	
	
private:

	FAoCAvatarData AvatarData;
};
