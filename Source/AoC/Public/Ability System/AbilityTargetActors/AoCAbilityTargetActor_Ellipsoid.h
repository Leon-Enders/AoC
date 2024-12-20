// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Form.h"
#include "AoCAbilityTargetActor_Ellipsoid.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_Ellipsoid : public AAoCAbilityTargetActor_Form
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Ellipsoid)
	FVector Radii;

protected:
	virtual void ConfirmTargeting() override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Tick(float DeltaSeconds) override;
private:

	TArray<TWeakObjectPtr<AActor>> GetActorsInEllipsoid(const FVector& Origin);
};
