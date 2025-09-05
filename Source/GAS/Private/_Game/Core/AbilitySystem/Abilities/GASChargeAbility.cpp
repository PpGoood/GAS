// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/Abilities/GASChargeAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

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
	//手动管理标签需要双端都同步不能
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	SourceASC->AddLooseGameplayTag(ChargeStateTag);
	
	bIsCharging = true;
	CurrentChargeTime = 0.0f;  // 重置蓄力时间
}

void UGASChargeAbility::ReleaseCharge()
{
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	SourceASC->RemoveLooseGameplayTag(ChargeStateTag);
	
	ActivateChargeAbility();
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true,false);
	bIsCharging = false;
	CurrentChargeTime = 0.0f;
}

void UGASChargeAbility::ActivateChargeAbility()
{
	UE_LOG(LogTemp, Display, TEXT("[PeiLog]111Activating Charge Ability"));
	UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	SourceASC->AddLooseGameplayTag(ActiveAbilityTag);
	//0.3秒后移除此标签
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this,SourceASC]()
	{
		// 移除标签
		SourceASC->RemoveLooseGameplayTag(ActiveAbilityTag);
	}, 0.3f, false);
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
