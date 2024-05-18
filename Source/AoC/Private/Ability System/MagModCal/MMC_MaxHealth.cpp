// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/MagModCal/MMC_MaxHealth.h"

#include "Ability System/AoCAttributeSet.h"
#include "Interaction/CombatSystemInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VitalityDef.AttributeToCapture = UAoCAttributeSet::GetVitalityAttribute();
	VitalityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	VitalityDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VitalityDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;
	
	float Vitality = 0.f;
	GetCapturedAttributeMagnitude(VitalityDef, Spec, AggregatorEvaluateParameters, Vitality);
	
	Vitality = FMath::Max<float>(0.f, Vitality);

	float PlayerLevel = 0.f;
	if(ICombatSystemInterface* CombatSystemInterfaceInterface = Cast<ICombatSystemInterface>(Spec.GetContext().GetSourceObject()))
	{
		PlayerLevel = CombatSystemInterfaceInterface->GetPlayerLevel();
	}
	
	return 80.f + Vitality * 20.f + PlayerLevel*10;	
}
