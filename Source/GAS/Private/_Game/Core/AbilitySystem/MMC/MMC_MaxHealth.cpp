// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MMC/MMC_MaxHealth.h"

#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDefinition.AttributeToCapture = UMyAttributeSet::GetVigorAttribute();
	VigorDefinition.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	VigorDefinition.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDefinition);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTages = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTages;
	EvaluateParameters.TargetTags = TargetTags;

	float Vigor = 0;
	GetCapturedAttributeMagnitude(VigorDefinition,Spec,EvaluateParameters,Vigor);
	Vigor = FMath::Max(Vigor,0);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetPlayerLevel();

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
