// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "UnderMouseDataAbilityTask.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseDataAbilityTask,const FGameplayAbilityTargetDataHandle&, DataHandle);
/**
 * 
 */
UCLASS()
class GAS_API UUnderMouseDataAbilityTask : public UAbilityTask
{
	GENERATED_BODY()

public:

	//默认条件下为自己
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks",meta=(DisplayName = "UnderMouseData",HidePin = "OwningAbility",DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly = "true"))
	static UUnderMouseDataAbilityTask* CreateUnderMouseDataAbilityTask(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FOnMouseDataAbilityTask OnMouseDataAbilityTask;


private:
	virtual void Activate() override;
	
	//客户端向服务器端提交数据
	void SendMouseCursorData();
	
	//当数据提交到服务器端后的委托回调
	void OnTargetDataReplicatedCallback(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivetionTag);
};
