// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/GASAssetManager.h"

#include "AbilitySystemGlobals.h"
#include "_Game/GameplayTagsInstance.h"

UGASAssetManager& UGASAssetManager::Get()
{
	check(GEngine);

	UGASAssetManager* GASAssetManager = Cast<UGASAssetManager>(GEngine->AssetManager);
	return *GASAssetManager;
}

void UGASAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	GameplayTagsInstance::GetInstance().InitNativeGameplayTags();

	//初始化数据，用来ASG的数据交互 5.4版本之后不需要调用 引擎自动调用初始化函数
	//UAbilitySystemGlobals::Get().InitGlobalData();
}
