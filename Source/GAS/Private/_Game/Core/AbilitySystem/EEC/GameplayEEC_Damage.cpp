// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/EEC/GameplayEEC_Damage.h"

#include "AbilitySystemComponent.h"
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"

//这里结构体不加F是因为它是内部结构体，不需要外部获取，也不需要在蓝图中使用
struct SDamageStatics 
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	//等价与
	// FProperty* ArmorProperty;
	// FGameplayEffectAttributeCaptureDefinition ArmorDef;
	SDamageStatics()
	{
		//参数：1.属性集 2.属性名 3.目标还是自身 4.是否设置快照（true为创建时获取，false为应用时获取）
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, BlockChance, Target, false);
		//等价与
		// ArmorProperty = FindFieldChecked<FProperty>(UMyAttributeSet::StaticClass(), GET_MEMBER_NAME_CHECKED(UMyAttributeSet, Armor));
		// ArmorDef = FGameplayEffectAttributeCaptureDefinition(ArmorProperty, EGameplayEffectAttributeCaptureSource::Target, false);
	}
};


static const SDamageStatics& DamageStatics()
{
	static SDamageStatics DStatics;
	return DStatics;
}


UGameplayEEC_Damage::UGameplayEEC_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
}

void UGameplayEEC_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                 FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	const AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	const AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	const FGameplayTagContainer* SourceTages = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTages;
	EvaluateParameters.TargetTags = TargetTags;

	float Damage = Spec.GetSetByCallerMagnitude(GameplayTagsInstance::GetInstance().Damage);
	
	float TargetBlockChance = 0;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef,EvaluateParameters,TargetBlockChance);
	TargetBlockChance = FMath::Max<float>(0, TargetBlockChance);

	const bool bBlocked = FMath::RandRange(1,100) < TargetBlockChance;
	if (bBlocked) Damage /= 2.f;

	float TargetArmor = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluateParameters, TargetArmor);
	TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

	float SourceArmorPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluateParameters, SourceArmorPenetration);
	SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

	const float EffectiveArmor = TargetArmor *= (100 - SourceArmorPenetration * 0.25f) / 100.f;
	Damage *= (100 - EffectiveArmor * 0.25f) / 100.f;
	
	const FGameplayModifierEvaluatedData EvaluatedData(UMyAttributeSet::GetIncomingDamageAttribute(),EGameplayModOp::Additive,Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
