// Copyright by Leon Enders ©, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AoCXPComponent.generated.h"

struct FGameplayTag;
class UAttributeSet;
class UAoCAttributeSet;
class UAoCXPDataAsset;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE_OneParam(FXPComponentChangedSignature, int32);


UCLASS()
class AOC_API UAoCXPComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	
	UAoCXPComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	void SetAttributeSet(UAttributeSet* AoCAttributeSet);

	

	FXPComponentChangedSignature OnLevelChanged;
	FXPComponentChangedSignature OnXPChanged;
	FXPComponentChangedSignature OnAttributePointsChanged;
	
	void LogLevel();
	void AddXP(const int32 InXP);
	
	void SetXP(const int32 InXP);
	void SetLevel(const int32 InLevel);
	void DecreaseAttributePoints();
	
	
	FORCEINLINE int32 GetLevel()const{return Level;}
	FORCEINLINE int32 GetAttributePoints()const{return AttributePoints;}
	float GetXPRatio()const;

	
private:
	UFUNCTION()
	void OnRep_Level();
	
	UFUNCTION()
	void OnRep_CurrentXP();

	UFUNCTION()
	void OnRep_AttributePoints();
	
	bool UpdateLevel(int32 InXP);
	
	UPROPERTY(ReplicatedUsing="OnRep_Level")
	int32 Level = 1;
	
	UPROPERTY(ReplicatedUsing="OnRep_CurrentXP")
	int32 CurrentXP = 0;

	UPROPERTY(ReplicatedUsing="OnRep_AttributePoints")
	int32 AttributePoints = 0;
	
	UPROPERTY(EditDefaultsOnly, Category="AbilitySystem")
	TObjectPtr<UAoCXPDataAsset> XPData;

	UPROPERTY()
	TObjectPtr<UAoCAttributeSet> AttributeSet;

	UFUNCTION(Reliable, Server, BlueprintCallable)
	void ApplyAttributePoint(const FGameplayTag& AttributeTag);
};
