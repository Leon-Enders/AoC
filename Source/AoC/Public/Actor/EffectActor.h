// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};

UCLASS()
class AOC_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AEffectActor();
	
	
protected:
	
	virtual void BeginPlay() override;
	
	
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void EndOverlap(AActor* TargetActor);
	
	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffect(TSubclassOf<UGameplayEffect> EffectToApply, AActor* TargetActor);
	
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InstantEffectApplyPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy DurationEffectApplyPolicy = EEffectApplicationPolicy::DoNotApply;

	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffect;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectApplicationPolicy InfiniteEffectApplyPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Applied Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveHandles;
};
