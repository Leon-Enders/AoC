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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void InitializeAvatarData(FName CharacterName);

	UFUNCTION(Client, Reliable)
	void UpdateAvatarDataClient(const FAoCAvatarData& AvatarDataFromServer);
	
	UAnimMontage* GetHitMontage()const;
	UAnimMontage* GetDeathMontage()const;
	UNiagaraSystem* GetBloodEffect()const;
	TArray<FGameplayTagMontage> GetGameplayTagMontages()const;
	float GetAvatarLifeSpan()const;
	
private:

	UPROPERTY(Replicated)
	FAoCAvatarData AvatarData;
};
