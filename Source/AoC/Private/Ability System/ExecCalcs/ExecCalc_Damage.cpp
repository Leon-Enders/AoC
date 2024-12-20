// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/ExecCalcs/ExecCalc_Damage.h"
#include "AoCGameplayTags.h"
#include "Ability System/AoCAbilitySystemLibrary.h"
#include "Ability System/AoCAttributeSet.h"


struct AoCDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Penetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);

	AoCDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, Defense, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, CritChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, CritDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAoCAttributeSet, Penetration, Source, false);
		
	}
};

static const AoCDamageStatics& DamageStatics()
{
	static AoCDamageStatics DStatics;
	return DStatics;
}



UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().DefenseDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().PenetrationDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
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
	
	
	float CritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritChanceDef, AggregatorEvaluateParameters, CritChance);
	CritChance = FMath::Max(0.f, CritChance);
	
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef, AggregatorEvaluateParameters, CritDamage);
	CritDamage = FMath::Max(0.f, CritDamage);
	

	float Penetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PenetrationDef, AggregatorEvaluateParameters, Penetration);
	Penetration = FMath::Max(0.f, Penetration);
	
	
	float Defense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().DefenseDef, AggregatorEvaluateParameters, Defense);
	Defense = FMath::Max(0.f, Defense);

	

	// Penetration ignores a percentage of the Targets Defense
	const float EffectiveArmor = ((100- Penetration)/100.f);

	//Armor ignores a percentage of incoming Damage + the amount of flat physical damage reduction

	float EffectiveDamageReduction = (100 - EffectiveArmor *0.1)/100.f-Defense/100.f;
	EffectiveDamageReduction = FMath::Clamp(EffectiveDamageReduction, 0.f, 1.f);

	
	Damage *= EffectiveDamageReduction;

	const bool bIsCriticalHit = FMath::RandRange(1, 100) <= CritChance * 10;

	// Update Effect Context
	FGameplayEffectContextHandle ContextHandle = OwningSpec.GetContext();
	UAoCAbilitySystemLibrary::SetIsCriticalHit(ContextHandle, bIsCriticalHit);


	
	Damage = bIsCriticalHit ? Damage*2.f+(Damage*CritDamage/100.f) : Damage;

	const FGameplayModifierEvaluatedData EvaluatedData(UAoCAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Override, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
