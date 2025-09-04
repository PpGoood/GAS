// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/Abilities/GASChargeAbility.h"

UGASChargeAbility::UGASChargeAbility()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGASChargeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	// 如果已经开始蓄力，返回
	if (bIsCharging)
	{
		return;
	}

	bIsCharging = true;
	CurrentChargeTime = 0.0f;  // 重置蓄力时间
}

void UGASChargeAbility::ReleaseCharge()
{
	
	// 在这里可以执行技能的释放逻辑
	// 例如：对敌人造成伤害，施加状态效果等
	ActivateChargeAbility();
	// 结束能力的激活
	bIsCharging = false;
	CurrentChargeTime = 0.0f;
}

void UGASChargeAbility::ChargeTick()
{
	// 增加蓄力时间，限制最大蓄力时间
	if (CurrentChargeTime < MaxChargeTime)
	{
		CurrentChargeTime += GetWorld()->GetDeltaSeconds();
	}
	else
	{
		// 蓄力达到最大值，执行释放
		ReleaseCharge();
	}

	// 打印蓄力时间
	FString ChargeTimeText = FString::Printf(TEXT("Current Charge Time: %.2f"), CurrentChargeTime);
	GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Yellow, ChargeTimeText);  // 输出在屏幕上
}

void UGASChargeAbility::InputPressed(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputPressed(Handle, ActorInfo, ActivationInfo);
	ChargeTick();
}

void UGASChargeAbility::InputReleased(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);
	ReleaseCharge();
}
