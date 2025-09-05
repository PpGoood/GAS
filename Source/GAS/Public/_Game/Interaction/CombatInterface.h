// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAS_API ICombatInterface
{
	GENERATED_BODY()
public:	
	virtual int32 GetPlayerLevel(){return 0;}

	//用于返回武器插槽的位置，用来生成特效
	virtual FVector GetCombatSocketLocation(){return FVector::ZeroVector;}

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& TargetLocation);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UAnimMontage* GetHitReactMontage(); //获取受击蒙太奇动画
	
	virtual void Die() = 0;
};
