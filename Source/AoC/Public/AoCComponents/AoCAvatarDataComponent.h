// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/Data/AoCAvatarDataInfo.h"
#include "Components/ActorComponent.h"
#include "AoCAvatarDataComponent.generated.h"



UCLASS( BlueprintType ,ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCAvatarDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAoCAvatarDataComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void InitializeAvatarData(FName CharacterName);
	
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetHitMontage()const;
	UFUNCTION(BlueprintCallable)
	UAnimMontage* GetDeathMontage()const;
	UFUNCTION(BlueprintCallable)
	UNiagaraSystem* GetBloodEffect()const;
	UFUNCTION(BlueprintCallable)
	TArray<FGameplayTagMontage> GetGameplayTagMontages()const;
	float GetAvatarLifeSpan()const;
	
private:

	UPROPERTY(Replicated)
	FAoCAvatarData AvatarData;
};
