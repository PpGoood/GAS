// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "_Game/Core/AbilitySystem/Abilities/GASDamageGameplayAbility.h"
#include "_Game/Data/WindAbilityDataAsset.h"
#include "GASChargeAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_API UGASChargeAbility : public UGASDamageGameplayAbility
{
	GENERATED_BODY()
public:
	UGASChargeAbility();

	// 设定蓄力的最大时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom|Charge Ability")
	float MaxChargeTime = 3.0f;  // 最大蓄力时间

	// 当前蓄力时间
	UPROPERTY(BlueprintReadOnly, Category = "Custom|Charge Ability")
	float CurrentChargeTime = 0.0f;

	// 蓄力状态
	UPROPERTY(BlueprintReadOnly, Category = "Custom|Charge Ability")
	bool bIsCharging = false;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Charge Ability|Tag")
	FGameplayTag ChargeStateTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom|Charge Ability|Tag")
	FGameplayTag ActiveAbilityTag;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	// 释放技能时的函数
	void ReleaseCharge();
	virtual void ActivateChargeAbility();
	// 在蓄力时持续调用
	void ChargeTick();
	virtual void InputPressed(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
	virtual void InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) override;
};
