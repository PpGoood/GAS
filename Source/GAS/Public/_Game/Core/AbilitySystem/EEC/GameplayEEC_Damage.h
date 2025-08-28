// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GameplayEEC_Damage.generated.h"

/**
 * Execution 适合写包含随机、分支、复杂逻辑的计算，因为它本来就不被预测。
 * 他执行在服务端
 */
UCLASS()
class GAS_API UGameplayEEC_Damage : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGameplayEEC_Damage();

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
