// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/ExecCalcs/ExecCalc_MagicDamage.h"

#include "AoCGameplayTags.h"
#include "Ability System/AoCAttributeSet.h"


struct AoCMagicDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicCritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);

	AoCMagicDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, MagicResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, MagicDamageReduction, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, MagicCritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, MagicPenetration, Source, false);
		
	}
};

static const AoCMagicDamageStatics& MagicDamageStatics()
{
	static AoCMagicDamageStatics DStatics;
	return DStatics;
}



UExecCalc_MagicDamage::UExecCalc_MagicDamage()
{
	RelevantAttributesToCapture.Add(MagicDamageStatics().MagicResistanceDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().MagicDamageReductionDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().MagicCritChanceDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(MagicDamageStatics().MagicPenetrationDef);
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
	
	
	float MagicCritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().MagicCritChanceDef, AggregatorEvaluateParameters, MagicCritChance);
	MagicCritChance = FMath::Max(0.f, MagicCritChance);
	
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().CritDamageDef, AggregatorEvaluateParameters, CritDamage);
	CritDamage = FMath::Max(0.f, CritDamage);

	float MagicResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().MagicResistanceDef, AggregatorEvaluateParameters, MagicResistance);
	MagicResistance = FMath::Max(0.f, MagicResistance);

	float MagicPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().MagicPenetrationDef, AggregatorEvaluateParameters, MagicPenetration);
	MagicPenetration = FMath::Max(0.f, MagicPenetration);
	
	
	float MagicDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(MagicDamageStatics().MagicDamageReductionDef, AggregatorEvaluateParameters, MagicDamageReduction);
	MagicDamageReduction = FMath::Max(0.f, MagicDamageReduction);

	

	// MagicPenetration ignores a percentage of the Targets MagicResistances
	const float EffectiveMagicResistance = MagicResistance * ((100- MagicPenetration)/100.f);
	
	//MagicResistances ignores a percentage of incoming magic Damage

	float EffectiveDamageReduction = (100 - EffectiveMagicResistance *0.1)/100.f-MagicDamageReduction/100.f;
	EffectiveDamageReduction = FMath::Clamp(EffectiveDamageReduction,0.f, 1.f);
	
	
	Damage *= EffectiveDamageReduction;

	const bool bIsCriticalHit = FMath::RandRange(1, 100) <= MagicCritChance * 10;
	
	Damage = bIsCriticalHit ? Damage*2.f+(Damage*CritDamage/100.f) : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAoCAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Override, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}