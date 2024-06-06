// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Ability System/AbilityTargetActors/AoCAbilityTargetActor_Form.h"
#include "AoCAbilityTargetActor_Cone.generated.h"

/**
 * 
 */
UCLASS()
class AOC_API AAoCAbilityTargetActor_Cone : public AAoCAbilityTargetActor_Form
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Cone)
	float ConeAngle;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (ExposeOnSpawn = true), Category = Cone)
	float ConeHeight;

protected:
	virtual void ConfirmTargeting() override;
	virtual void ConfirmTargetingAndContinue() override;
	virtual void Tick(float DeltaSeconds) override;
private:

	TArray<TWeakObjectPtr<AActor>> GetActorsInCone(const FVector& Origin);
};
