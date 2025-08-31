// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/EEC/GameplayEEC_Damage.h"

#include "AbilitySystemComponent.h"
#include "_Game/GameplayTagsInstance.h"
#include "_Game/Core/AbilitySystem/MyAttributeSet.h"
#include "_Game/Core/AbilitySystem/Data/CharacterClassInfo.h"
#include "_Game/Interaction/CombatInterface.h"
#include "_Game/Util/GASBlueprintFunctionLibrary.h"

//这里结构体不加F是因为它是内部结构体，不需要外部获取，也不需要在蓝图中使用
struct SDamageStatics 
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	
	//等价与
	// FProperty* ArmorProperty;
	// FGameplayEffectAttributeCaptureDefinition ArmorDef;
	SDamageStatics()
	{
		//参数：1.属性集 2.属性名 3.目标还是自身 4.是否设置快照（true为创建时获取，false为应用时获取）
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, Armor, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, CriticalHitDamage, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UMyAttributeSet, CriticalHitResistance, Target, false);

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
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
}

void UGameplayEEC_Damage::Execute_Implementation(
    const FGameplayEffectCustomExecutionParameters& ExecutionParams,
    FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
    // =========================
    // 1️⃣ 获取源和目标能力系统组件与 Actor
    // =========================
    const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
    const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

    AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
    AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

    ICombatInterface* SourceCombatInterface = Cast<ICombatInterface>(SourceAvatar);
    ICombatInterface* TargetCombatInterface = Cast<ICombatInterface>(TargetAvatar);

    // =========================
    // 2️⃣ 获取 GameplayEffect 规格和标签
    // =========================
    const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();
    const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
    const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

    FAggregatorEvaluateParameters EvalParams;
    EvalParams.SourceTags = SourceTags;
    EvalParams.TargetTags = TargetTags;

    // =========================
    // 3️⃣ 获取基础伤害值
    // =========================
    float Damage = Spec.GetSetByCallerMagnitude(GameplayTagsInstance::GetInstance().Damage);

    // =========================
    // 4️⃣ 计算目标属性：格挡、护甲、暴击抵抗等
    // =========================
    float TargetBlockChance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvalParams, TargetBlockChance);
    TargetBlockChance = FMath::Max(0.f, TargetBlockChance);

    float TargetArmor = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvalParams, TargetArmor);
    TargetArmor = FMath::Max(0.f, TargetArmor);

    float SourceArmorPenetration = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvalParams, SourceArmorPenetration);
    SourceArmorPenetration = FMath::Max(0.f, SourceArmorPenetration);

    float SourceCriticalHitChance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvalParams, SourceCriticalHitChance);
    SourceCriticalHitChance = FMath::Max(0.f, SourceCriticalHitChance);

    float SourceCriticalHitDamage = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvalParams, SourceCriticalHitDamage);
    SourceCriticalHitDamage = FMath::Max(0.f, SourceCriticalHitDamage);

    float TargetCriticalHitResistance = 0.f;
    ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvalParams, TargetCriticalHitResistance);
    TargetCriticalHitResistance = FMath::Max(0.f, TargetCriticalHitResistance);

    // =========================
    // 5️⃣ 获取伤害计算曲线系数
    // =========================
    const UCharacterClassInfo* CharacterClassInfo = UGASBlueprintFunctionLibrary::GetCharacterClassInfo(SourceAvatar);

    const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationTable->FindCurve(FName("ArmorPenetration"), FString());
    const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationTable->FindCurve(FName("EffectiveArmor"), FString());
    const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationTable->FindCurve(FName("CriticalHitResistance"), FString());

    const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourceCombatInterface->GetPlayerLevel());
    const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetCombatInterface->GetPlayerLevel());
    const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetCombatInterface->GetPlayerLevel());

    // =========================
    // 6️⃣ 格挡判定
    // =========================
    const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
    if (bBlocked)
    {
        Damage /= 2.f; // 格挡后伤害减半
    }

    // =========================
    // 7️⃣ 护甲与护甲穿透计算
    // =========================
    const float EffectiveArmor = TargetArmor * (100 - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f;
    Damage *= (100 - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;

    // =========================
    // 8️⃣ 暴击判定
    // =========================
    const float EffectiveCriticalHitChance = SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient;
    const bool bCriticalHit = FMath::RandRange(1, 100) < EffectiveCriticalHitChance;

    if (bCriticalHit)
    {
        Damage = Damage * 2.f + SourceCriticalHitDamage; // 暴击加成
    }

    // =========================
    // 9️⃣ 输出伤害
    // =========================
    const FGameplayModifierEvaluatedData EvaluatedData(
        UMyAttributeSet::GetIncomingDamageAttribute(),
        EGameplayModOp::Additive,
        Damage
    );

	// =========================
	// 9️⃣ GE自定义上下文赋值字段
	// =========================
	UGASBlueprintFunctionLibrary::SetIsBlockedHit(EffectContextHandle,bBlocked);
	UGASBlueprintFunctionLibrary::SetIsCriticalHit(EffectContextHandle,bCriticalHit);
    OutExecutionOutput.AddOutputModifier(EvaluatedData);
}
