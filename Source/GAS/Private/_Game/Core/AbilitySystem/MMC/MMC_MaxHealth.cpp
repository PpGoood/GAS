// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/MMC/MMC_MaxHealth.h"

#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Interaction/CombatInterface.h"

/**
 * FGameplayEffectAttributeCaptureDefinition&	你在 MMC 构造函数里定义的属性捕获规则（捕获哪个属性、来源、是否快照）
 * Spec	FGameplayEffectSpec&	当前正在应用的 GE 实例，包含源/目标信息、Effect上下文、标签等
 * EvaluationParameters	FAggregatorEvaluateParameters&	计算上下文参数，包括 Source/Target 标签、忽略的 GE、预测 Modifier 等
 * Magnitude	float&	输出参数，返回捕获的属性最终值（经过标签和 Modifier 计算）
 */


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
