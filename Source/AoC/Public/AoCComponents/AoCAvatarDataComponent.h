// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Data/AoCAvatarDataInfo.h"
#include "Components/ActorComponent.h"
#include "AoCAvatarDataComponent.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCAvatarDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAoCAvatarDataComponent();
	void InitializeAvatarData(FName CharacterName);

	UAnimMontage* GetHitMontage()const;
	UAnimMontage* GetDeathMontage()const;
	UNiagaraSystem* GetBloodEffect()const;
	TArray<FGameplayTagMontage> GetGameplayTagMontages()const;
	float GetAvatarLifeSpan()const;
	
private:

	FAoCAvatarData AvatarData;
};
