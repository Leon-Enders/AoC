// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AoCProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class AOC_API AAoCProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AAoCProjectile();

protected:
	
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Projectile")
	TObjectPtr<USphereComponent> SphereComponent;
	

};
