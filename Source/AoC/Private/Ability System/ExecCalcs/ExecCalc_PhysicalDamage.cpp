// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/ExecCalcs/ExecCalc_PhysicalDamage.h"

#include "AoCGameplayTags.h"
#include "Ability System/AoCAttributeSet.h"


struct AoCDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalCritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);

	AoCDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, PhysicalDamageReduction, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, PhysicalCritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, ArmorPenetration, Source, false);
		
	}
};

static const AoCDamageStatics& DamageStatics()
{
	static AoCDamageStatics DStatics;
	return DStatics;
}



UExecCalc_PhysicalDamage::UExecCalc_PhysicalDamage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalCritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
}

void UExecCalc_PhysicalDamage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
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
	
	
	float PhysicalCritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalCritChanceDef, AggregatorEvaluateParameters, PhysicalCritChance);
	PhysicalCritChance = FMath::Max(0.f, PhysicalCritChance);
	
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, AggregatorEvaluateParameters, CritDamage);
	CritDamage = FMath::Max(0.f, CritDamage);

	float armor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, AggregatorEvaluateParameters, armor);
	armor = FMath::Max(0.f, armor);

	float ArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, AggregatorEvaluateParameters, ArmorPenetration);
	ArmorPenetration = FMath::Max(0.f, ArmorPenetration);
	
	
	float PhysicalDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageReductionDef, AggregatorEvaluateParameters, PhysicalDamageReduction);
	PhysicalDamageReduction = FMath::Max(0.f, PhysicalDamageReduction);

	
	


	
}
