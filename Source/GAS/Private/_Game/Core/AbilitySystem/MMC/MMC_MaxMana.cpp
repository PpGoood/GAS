// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MMC/MMC_MaxMana.h"

#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Interaction/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDefinition.AttributeToCapture = UMyAttributeSet::GetIntelligenceAttribute();
	IntelligenceDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	IntelligenceDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(IntelligenceDefinition);
	
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTages = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTages;
	EvaluateParameters.TargetTags = TargetTags;

	float Intelligence = 0;
	GetCapturedAttributeMagnitude(IntelligenceDefinition,Spec,EvaluateParameters,Intelligence);
	Intelligence = FMath::Max(Intelligence,0);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 50.f + 2.5f * Intelligence + 10.f * PlayerLevel;
}
