// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCComponents/AoCComponent.h"
#include "AoCXPComponent.generated.h"

class UAoCXPDataAsset;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FXPComponentChangedSignature, int32);


UCLASS()
class AOC_API UAoCXPComponent : public UAoCComponent
{
	GENERATED_BODY()
	
public:
	
	UAoCXPComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void InitializeAoCComponent() override;

	

	FXPComponentChangedSignature OnLevelChanged;
	FXPComponentChangedSignature OnXPChanged;
	
	UFUNCTION(BlueprintCallable)
	void LogLevel();
	
	UFUNCTION(BlueprintCallable)
	void AddXP(const int32 InXP);
	
	void SetXP(const int32 InXP);
	void SetLevel(const int32 InLevel);
	
	FORCEINLINE int32 GetLevel()const{return Level;}
	float GetXPRatio()const;
	
private:
	
	UFUNCTION()
	void OnRep_Level();
	
	UFUNCTION()
	void OnRep_CurrentXP();
	
	bool UpdateLevel(int32 InXP);
	
	UPROPERTY(ReplicatedUsing="OnRep_Level")
	int32 Level = 1;
	
	UPROPERTY(ReplicatedUsing="OnRep_CurrentXP")
	int32 CurrentXP = 0;
	
	float XPRatio = 0.f;
	
	UPROPERTY(EditAnywhere, Category="AbilitySystem")
	TObjectPtr<UAoCXPDataAsset> XPData;
};
