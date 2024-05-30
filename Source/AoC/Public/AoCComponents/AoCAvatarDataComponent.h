// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponent.h"
#include "Data/AoCAvatarDataAsset.h"
#include "AoCAvatarDataComponent.generated.h"


class UAoCAvatarDataAsset;

UCLASS( BlueprintType, Blueprintable ,ClassGroup=(AoCComponents), meta=(BlueprintSpawnableComponent) )
class AOC_API UAoCAvatarDataComponent : public UAoCComponent
{
	GENERATED_BODY()

public:	
	
	UAoCAvatarDataComponent();
	virtual void InitializeAoCComponent(FName CharacterName) override;
	
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

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAoCAvatarDataAsset> AvatarData;
};
