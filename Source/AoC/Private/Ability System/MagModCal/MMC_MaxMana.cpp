// Copyright by Leon Enders ©, All Rights Reserved.


#include "Ability System/MagModCal/MMC_MaxMana.h"

#include "Ability System/AoCAttributeSet.h"
#include "Interaction/AoCAvatarDataInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UAoCAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntelligenceDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDef);
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters AggregatorEvaluateParameters;
	AggregatorEvaluateParameters.SourceTags = SourceTags;
	AggregatorEvaluateParameters.TargetTags = TargetTags;
	
	float Intelligence = 0.f;
	GetCapturedAttributeMagnitude(IntelligenceDef, Spec, AggregatorEvaluateParameters, Intelligence);
	
	Intelligence = FMath::Max<float>(0.f, Intelligence);

	const float PlayerLevel = IAoCAvatarDataInterface::Execute_GetPlayerLevel(Spec.GetContext().GetSourceObject());
	
	return 80.f + Intelligence * 30.f + PlayerLevel*20;	
}
