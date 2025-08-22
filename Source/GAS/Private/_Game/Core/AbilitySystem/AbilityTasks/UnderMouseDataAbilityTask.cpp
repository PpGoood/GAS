// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Core/AbilitySystem/AbilityTasks/UnderMouseDataAbilityTask.h"

#include "AbilitySystemComponent.h"

UUnderMouseDataAbilityTask* UUnderMouseDataAbilityTask::CreateUnderMouseDataAbilityTask(UGameplayAbility* OwningAbility)
{
	UUnderMouseDataAbilityTask* Task = NewAbilityTask<UUnderMouseDataAbilityTask>(OwningAbility);
	return Task;
}

//客户端请求发送数据
//服务端尝试去调用收到数据的回调
//如果没有收到数据则等待收到数据
//回调让客户端清除数据
void UUnderMouseDataAbilityTask::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		FGameplayAbilitySpecHandle SpecHandle = GetAbilitySpecHandle();
		FPredictionKey ActivationPredictionKey = GetActivationPredictionKey();
		AbilitySystemComponent.Get()->AbilityTargetDataSetDelegate(SpecHandle,ActivationPredictionKey).
		AddUObject(this,&ThisClass::OnTargetDataReplicatedCallback);
		const bool bCalledDelegate = AbilitySystemComponent.Get()->CallReplicatedTargetDataDelegatesIfSet(SpecHandle,ActivationPredictionKey);
		if (!bCalledDelegate)
		{
			SetWaitingOnRemotePlayerData();
		}
	}
}

void UUnderMouseDataAbilityTask::SendMouseCursorData()
{

	FScopedPredictionWindow ScopedPredictionWindow(AbilitySystemComponent.Get(),true);
	
	APlayerController* PlayerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult CursorHit; 
	PlayerController->GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);

	FGameplayAbilityTargetData_SingleTargetHit* Data = new FGameplayAbilityTargetData_SingleTargetHit();
	Data->HitResult = CursorHit;

	FGameplayAbilityTargetDataHandle DataHandle;
	DataHandle.Add(Data);

	AbilitySystemComponent->ServerSetReplicatedTargetData(
		GetAbilitySpecHandle(),
		GetActivationPredictionKey(),
		DataHandle,
		FGameplayTag(),
		AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnMouseDataAbilityTask.Broadcast(DataHandle);
	}
}

void UUnderMouseDataAbilityTask::OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,
	FGameplayTag ActivetionTag)
{
	//通知客户端 服务器端已经接收并处理了从客户端复制的目标数据（将服务器的TargetData应用到客户端，并清除掉缓存）
	AbilitySystemComponent->ConsumeClientReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey());
	//判断服务器端是否通过验证
	if(ShouldBroadcastAbilityTaskDelegates())
	{
		OnMouseDataAbilityTask.Broadcast(DataHandle);
	}
}

