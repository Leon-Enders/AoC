// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UGameplayEffect;


UCLASS()
class AOC_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEffectActor();
	
	
protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category="Applied Effects")
	TObjectPtr<UGameplayEffect> InstantGameplayEffect;


	UPROPERTY(EditAnywhere, Category="Applied Effects")
	TObjectPtr<UGameplayEffect> DurationGameplayEffect;

	UPROPERTY(EditAnywhere, Category="Applied Effects")
	TObjectPtr<UGameplayEffect> InfiniteGameplayEffect;
};
