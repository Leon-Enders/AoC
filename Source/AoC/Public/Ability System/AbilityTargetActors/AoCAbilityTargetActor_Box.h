// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Form.h"
#include "AoCAbilityTargetActor_Box.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_Box : public AAoCAbilityTargetActor_Form
{
	GENERATED_BODY()
public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Sphere)
	FVector BoxHalfExtent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Sphere)
	bool bUseAimRotation = false;
	
protected:
	virtual void ConfirmTargeting() override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Tick(float DeltaSeconds) override;
private:

	TArray<TWeakObjectPtr<AActor>> GetActorsInBox(const FVector& Origin);
};
