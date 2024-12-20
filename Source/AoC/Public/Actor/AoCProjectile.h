// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "AoCProjectile.generated.h"

class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AOC_API AAoCProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAoCProjectile();
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(BlueprintReadOnly, meta =(ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageHandle;



protected:
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly)
	float LifeTime = 15.f;

	bool bHit = false;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void Destroyed() override;
	
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComponent;

	UPROPERTY(EditDefaultsOnly, Category="ProjectileProperties")
	TObjectPtr<UNiagaraSystem> ExplosionEffect;
	
};
