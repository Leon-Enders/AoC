// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/ExecCalcs/ExecCalc_MagicDamage.h"
#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/AoCAttributeSet.h"


struct AoCMagicDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Power);
	DECLARE_ATTRIBUTE_CAPTUREDEF(HealingPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);

	AoCMagicDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, DamageReduction, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, Power, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, HealingPower, Source, false);
		
	}
};

static const AoCMagicDamageStatics& MagicDamageStatics()
{
	static AoCMagicDamageStatics DStatics;
	return DStatics;
}



UExecCalc_MagicDamage::UExecCalc_MagicDamage()
{
	RelevantAttributesToCapture.Add(MagicDamageStatics().DamageReductionDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().PowerDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().HealingPowerDef);
}

void UExecCalc_MagicDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                      FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	Super::Execute_Implementation(ExecutionParams, OutExecutionOutput);

	UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();


	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = SourceASC ? TargetASC->GetAvatarActor() : nullptr;
	
	const FGameplayEffectSpec& OwningSpec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTags = OwningSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = OwningSpec.CapturedTargetTags.GetAggregatedTags();


	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;

	
	
	float Damage = OwningSpec.GetSetByCallerMagnitude(FAoCGameplayTags::Get().Damage);
	
	
	float Power = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().PowerDef, AggregatorEvaluateParameters, Power);
	Power = FMath::Max(0.f, Power);
	
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().CritDamageDef, AggregatorEvaluateParameters, CritDamage);
	CritDamage = FMath::Max(0.f, CritDamage);

	float HealingPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().HealingPowerDef, AggregatorEvaluateParameters, HealingPower);
	HealingPower = FMath::Max(0.f, HealingPower);
	
	
	float DamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().DamageReductionDef, AggregatorEvaluateParameters, DamageReduction);
	DamageReduction = FMath::Max(0.f, DamageReduction);
	
	
	//MagicResistances ignores a percentage of incoming magic Damage

	float EffectiveDamageReduction = (100 - 0.1)/100.f-DamageReduction/100.f;
	EffectiveDamageReduction = FMath::Clamp(EffectiveDamageReduction,0.f, 1.f);
	
	
	Damage *= EffectiveDamageReduction;

	const bool bIsCriticalHit = FMath::RandRange(1, 100) <= Power * 10;

	// Update Effect Context
	FGameplayEffectContextHandle ContextHandle = OwningSpec.GetContext();
	UAoCAbilitySystemLibrary::SetIsCriticalHit(ContextHandle, bIsCriticalHit);

	
	Damage = bIsCriticalHit ? Damage*2.f+(Damage*CritDamage/100.f) : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAoCAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Override, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}