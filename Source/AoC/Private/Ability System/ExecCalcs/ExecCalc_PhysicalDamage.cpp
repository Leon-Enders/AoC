// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/ExecCalcs/ExecCalc_PhysicalDamage.h"

#include "AoCGameplayTags.h"
#include "Ability System/AoCAttributeSet.h"


struct AoCPhysicalDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalCritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);

	AoCPhysicalDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, PhysicalDamageReduction, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, PhysicalCritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, ArmorPenetration, Source, false);
		
	}
};

static const AoCPhysicalDamageStatics& PhysicalDamageStatics()
{
	static AoCPhysicalDamageStatics DStatics;
	return DStatics;
}



UExecCalc_PhysicalDamage::UExecCalc_PhysicalDamage()
{
	RelevantAttributesToCapture.Add(PhysicalDamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(PhysicalDamageStatics().PhysicalDamageReductionDef);
	RelevantAttributesToCapture.Add(PhysicalDamageStatics().PhysicalCritChanceDef);
	RelevantAttributesToCapture.Add(PhysicalDamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(PhysicalDamageStatics().ArmorPenetrationDef);
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
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageStatics().PhysicalCritChanceDef, AggregatorEvaluateParameters, PhysicalCritChance);
	PhysicalCritChance = FMath::Max(0.f, PhysicalCritChance);
	
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageStatics().CritDamageDef, AggregatorEvaluateParameters, CritDamage);
	CritDamage = FMath::Max(0.f, CritDamage);

	float Armor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageStatics().ArmorDef, AggregatorEvaluateParameters, Armor);
	Armor = FMath::Max(0.f, Armor);

	float ArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageStatics().ArmorPenetrationDef, AggregatorEvaluateParameters, ArmorPenetration);
	ArmorPenetration = FMath::Max(0.f, ArmorPenetration);
	
	
	float PhysicalDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(PhysicalDamageStatics().PhysicalDamageReductionDef, AggregatorEvaluateParameters, PhysicalDamageReduction);
	PhysicalDamageReduction = FMath::Max(0.f, PhysicalDamageReduction);

	

	// ArmorPenetration ignores a percentage of the Targets Armor
	const float EffectiveArmor = Armor * ((100- ArmorPenetration)/100.f);

	//Armor ignores a percentage of incoming Damage + the amount of flat physical damage reduction

	float EffectiveDamageReduction = (100 - EffectiveArmor *0.1)/100.f-PhysicalDamageReduction/100.f;
	EffectiveDamageReduction = FMath::Clamp(EffectiveDamageReduction, 0.f, 1.f);

	
	Damage *= EffectiveDamageReduction;

	const bool bIsCriticalHit = FMath::RandRange(1, 100) <= PhysicalCritChance * 10;
	
	Damage = bIsCriticalHit ? Damage*2.f+(Damage*CritDamage/100.f) : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAoCAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Override, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
